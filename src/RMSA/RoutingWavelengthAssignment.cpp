#include <RMSA/RoutingWavelengthAssignment.h>
#include <algorithm>
#include <GeneralClasses/ModulationScheme.h>
#include <RMSA/Route.h>
#include <RMSA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <RMSA/SpectrumAssignmentAlgorithms/SpectrumAssignmentAlgorithm.h>
#include <RMSA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>
#include <RMSA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>
#include <Structure/Topology.h>

using namespace RMSA;
using namespace ROUT;
using namespace SA;
using namespace RA;

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm> R_Alg,
    std::shared_ptr<SpectrumAssignmentAlgorithm> WA_Alg,
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg,
    std::vector<ModulationScheme> Schemes,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg), WA_Alg(WA_Alg), RA_Alg(RA_Alg), Schemes(Schemes), T(T)
{

}

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm>  R_Alg,
    std::shared_ptr<SpectrumAssignmentAlgorithm> WA_Alg,
    std::vector<ModulationScheme> Schemes,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg), WA_Alg(WA_Alg), Schemes(Schemes), T(T)
{

    RA_Alg = nullptr;

}

std::shared_ptr<Route> RoutingWavelengthAssignment::routeCall(
    std::shared_ptr<Call> C)
{

    std::vector<std::weak_ptr<Link>> Links;
    std::vector<TransparentSegment> Segments;
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>, std::owner_less<std::weak_ptr<Link>>>
            Slots;

    if (RA_Alg == nullptr)
        {
        std::sort(Schemes.rbegin(), Schemes.rend());

        for (auto &scheme : Schemes)
            {
            C->Scheme = scheme;
            Links = R_Alg->route(C);

            if (Links.empty())
                {
                C->Status = Call::Blocked;
                return nullptr;
                }

            TransparentSegment Segment(Links, scheme, 0);

            auto SegmentSlots = WA_Alg->assignSlots(C, Segment);
            if (SegmentSlots.empty())
                {
                if (scheme == Schemes.back())
                    {
                    C->Status = Call::Blocked;
                    return nullptr;
                    }
                continue;
                }

            Signal S(SegmentSlots);
            S = Segment.bypass(S);

            Segments.push_back(Segment); // COMENT. AUX.: Trouxe de cima do if acima.

            if ((!considerAseNoise ||
                    S.get_OSNR() >= scheme.get_ThresholdOSNR(C->Bitrate)) &&
                    (!considerFilterImperfection ||
                     S.get_SignalPowerRatio() >= T->get_PowerRatioThreshold()))
                {                
                Slots.insert(SegmentSlots.begin(), SegmentSlots.end());

                // Teste
                unsigned int auxCount = 0;
                for(auto& link : Slots)
                {
                    //(link.first).lock()->tempSpecDensity = Segment.opticalPathSpecDensity.at(auxCount);
                    auxCount++;
                }

                if(Slots.begin()->second.size() * 25 != Segment.opticalPathSpecDensity.begin()->specDensity.n_cols)
                    std::cout << std::endl << "FLAG Rout." << std::endl;
                // Teste

                break;
                }
            else if (scheme == Schemes.back())
                {
                C->Status = Call::Blocked;
                return nullptr;
                }
            }
        }
    else
        {
        Links = R_Alg->route(C);        

        RA_Alg->thisRMSA = this;

        if (Links.empty())
            {
            C->Status = Call::Blocked;
            return nullptr;
            }

        Segments = RA_Alg->assignRegenerators(C, Links);

        if (Segments.empty())
            {
            C->Status = Call::Blocked;
            return nullptr;
            }

        for (auto &segment : Segments)
            {
            auto SegmentSlots = WA_Alg->assignSlots(C, segment);

            if (SegmentSlots.empty())
                {
                C->Status = Call::Blocked;
                Slots.clear();
                return nullptr;
                }

            Slots.insert(SegmentSlots.begin(), SegmentSlots.end());
            }
        }

    if (C->Status == Call::Not_Evaluated)
        {
        C->Status = Call::Implemented;
        }

    return std::shared_ptr<Route>(new Route(Segments, Slots));
}
