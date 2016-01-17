#include <RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction.h>
#include <RWA/RoutingAlgorithms/StaticRouting/ShortestPath.h>
#include <RWA/WavelengthAssignmentAlgorithms/FirstFit.h>
#include <RWA/RoutingWavelengthAssignment.h>
#include <Calls.h>

SignalQualityPrediction::SignalQualityPrediction(std::shared_ptr<Topology> T,
        std::shared_ptr<RoutingWavelengthAssignment> RWA,
        double NetworkLoad,
        unsigned long long NumCalls,
        std::vector<TransmissionBitrate> Bitrates) :
    NX_RegeneratorPlacement(T), RWA(RWA), NetworkLoad(NetworkLoad),
    NumCalls(NumCalls), Bitrates(Bitrates)
{
    evaluateLNMax();
}

void SignalQualityPrediction::placeRegenerators(unsigned, unsigned)
{

}

void SignalQualityPrediction::evaluateLNMax()
{
    auto SP = std::make_shared<ShortestPath>(T);

    for (auto &bitrate : Bitrates)
        {
        for (auto &scheme : ModulationScheme::DefaultSchemes)
            {

            auto BitSchemePair = std::make_pair(bitrate, scheme);
            unsigned maxLN = 0;

            for (auto &orig : T->Nodes)
                {
                for (auto &dest : T->Nodes)
                    {
                    if (orig == dest)
                        {
                        continue;
                        }

                    auto DummyCall = std::make_shared<Call>(orig, dest, bitrate);
                    DummyCall->Scheme = scheme;

                    auto links = SP->route(DummyCall);
                    Signal S;

                    if ((links.size() > maxLN) &&
                            (TransparentSegment(links, scheme).bypass(S).get_OSNR() >=
                             scheme.get_ThresholdOSNR(bitrate)))
                        {
                        maxLN = links.size();
                        }
                    }
                }

            LNMax.emplace(BitSchemePair, maxLN);
            }
        }
}
