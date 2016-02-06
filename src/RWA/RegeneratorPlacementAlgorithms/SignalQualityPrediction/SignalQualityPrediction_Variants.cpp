#include "include/RWA/RegeneratorPlacementAlgorithms/SignalQualityPrediction/SignalQualityPrediction_Variants.h"
#include "RWA/RoutingAlgorithms.h"
#include <Calls/Call.h>
#include <Structure/Topology.h>
#include <RWA/TransparentSegment.h>
#include <boost/assign.hpp>

SignalQualityPrediction_Variants::SQPVariantNameBimap
SignalQualityPrediction_Variants::SQPVariantNames =
    boost::assign::list_of<SignalQualityPrediction_Variants::SQPVariantNameBimap::relation>
#define X(a,b) (a,b)
    SQPVARIANTS
#undef X
#undef SQPVARIANTS
    ;

SignalQualityPrediction_Variants::SQP_Variants
SignalQualityPrediction_Variants::Variant;
bool SignalQualityPrediction_Variants::chooseVariant = false;

SignalQualityPrediction_Variants::SignalQualityPrediction_Variants(
    std::shared_ptr<Topology> T, std::shared_ptr<RoutingWavelengthAssignment> RWA,
    double NetworkLoad, unsigned long long NumCalls,
    std::vector<TransmissionBitrate> Bitrates) :
    SignalQualityPrediction(T, RWA, NetworkLoad, NumCalls, Bitrates)
{
    chooseSQPVariant();
    evaluateLNMax();
}

void SignalQualityPrediction_Variants::load()
{
    NX_RegeneratorPlacement::load();
}

void SignalQualityPrediction_Variants::chooseSQPVariant()
{
    if (chooseVariant)
        {
        return;
        }

    std::cout << std::endl << "-> Choose a SQP Variant." << std::endl;
    do
        {
        for (auto &variant : SQPVariantNames.left)
            {
            std::cout << "(" << variant.first << ")\t" << variant.second << std::endl;
            }

        int chosenSQPVariant;
        std::cin >> chosenSQPVariant;

        if (std::cin.fail() || SQPVariantNames.left.count
                ((SQP_Variants) chosenSQPVariant) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid regenerator placement algorithm." << std::endl;
            std::cout << std::endl << "-> Choose a SQP Variant." << std::endl;
            }
        else
            {
            Variant = (SQP_Variants) chosenSQPVariant;
            chooseVariant = true;
            break;
            }
        }
    while (1);
}

void SignalQualityPrediction_Variants::evaluateLNMax()
{
    std::shared_ptr<StaticRoutingAlgorithm> RAlg;

    //Choose adequate Routing Algorithm
    switch (Variant)
        {
        case mSCH_MH:
        case MSCH_MH:
            RAlg = std::make_shared<MinimumHops>(T);
            break;

        case mSCH_SP:
        case MSCH_SP:
            RAlg = std::make_shared<ShortestPath>(T);
            break;
        }

    auto Schemes = ModulationScheme::DefaultSchemes;
    ModulationScheme scheme = Schemes.front();
    std::sort(Schemes.rbegin(), Schemes.rend());

    //Choose adequate Modulation Scheme
    switch (Variant)
        {
        case mSCH_MH:
        case mSCH_SP:
            scheme = Schemes.back();
            break;

        case MSCH_MH:
        case MSCH_SP:
            scheme = Schemes.front();
            break;
        }

    std::sort(Bitrates.rbegin(), Bitrates.rend());
    auto bitrate = Bitrates.front(); //Greatest possible bitrate

    unsigned maxLN = LNMax.at(std::make_pair(bitrate, scheme));

    for (auto &ln_pair : LNMax)
        {
        ln_pair.second = maxLN;
        }
}
