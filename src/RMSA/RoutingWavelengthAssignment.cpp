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
    std::set<ModulationScheme> Schemes,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg), WA_Alg(WA_Alg), RA_Alg(RA_Alg), Schemes(Schemes), T(T)
{

}

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm>  R_Alg,
    std::shared_ptr<SpectrumAssignmentAlgorithm> WA_Alg,
    std::set<ModulationScheme> Schemes,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg), WA_Alg(WA_Alg), Schemes(Schemes), T(T)
{

    RA_Alg = nullptr;

}

std::shared_ptr<Route> RoutingWavelengthAssignment::routeCall(
    std::shared_ptr<Call> C)
{
    if (RA_Alg == nullptr)
        {
        return routeCall_Transparent(C);
        }
    else
        {
        return routeCall_Translucent(C);
        }
}

std::shared_ptr<Route>
RoutingWavelengthAssignment::routeCall_Transparent(std::shared_ptr<Call> C)
{
    std::vector<std::vector<std::weak_ptr<Link>>> possibleRoutes;
    std::vector<TransparentSegment> Segments;
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;

    for (auto schPtr = Schemes.rbegin(); schPtr != Schemes.rend(); ++schPtr)
        {
        auto scheme = *schPtr;
        C->Scheme = scheme;
        possibleRoutes = R_Alg->route(C);

        //There's no route
        if (possibleRoutes.empty() || possibleRoutes.front().empty())
            {
            C->Status = Call::Blocked;
            return nullptr;
            }

        for (auto &route : possibleRoutes)
            {
            Segments.clear();
            Slots.clear();
            C->Status = Call::Not_Evaluated;

            TransparentSegment Segment(route, scheme, 0);

            auto SegmentSlots = WA_Alg->assignSlots(C, Segment);
            if (SegmentSlots.empty())
                {
                if (scheme == *(Schemes.begin()))
                    {
                    C->Status = Call::Blocked;
                    return nullptr;
                    }
                continue;
                }

            Signal S(SegmentSlots);
            S = Segment.bypass(S);

            if (
                (!considerAseNoise ||
                 S.get_OSNR() >= scheme.get_ThresholdOSNR(C->Bitrate)) &&
                (!considerFilterImperfection ||
                 S.get_SignalPowerRatio() >= T->get_PowerRatioThreshold()))
                {
                Slots.insert(SegmentSlots.begin(), SegmentSlots.end());
                Segments.push_back(Segment);
                break;
                }
            //There's no quality with any scheme
            else if (scheme == *(Schemes.begin()))
                {
                C->Status = Call::Blocked;
                continue;
                }
            }

        if (!Slots.empty())
            {
            break;
            }
        }

    if (C->Status == Call::Not_Evaluated)
        {
        C->Status = Call::Implemented;
        }

    return std::shared_ptr<Route>(new Route(Segments, Slots));
}

std::shared_ptr<Route>
RoutingWavelengthAssignment::routeCall_Translucent(std::shared_ptr<Call> C)
{
    std::vector<std::vector<std::weak_ptr<Link>>> possibleRoutes;
    std::vector<TransparentSegment> Segments;
    mapSlots Slots;

    RA_Alg->thisRMSA = this;
    possibleRoutes = R_Alg->route(C);

    //There's no route
    if (possibleRoutes.empty() || possibleRoutes.front().empty())
        {
        C->Status = Call::Blocked;
        return nullptr;
        }

    for (auto &route : possibleRoutes)
        {
        C->Status = Call::Not_Evaluated;
        Segments = RA_Alg->assignRegenerators(C, route);

        //There are no regenerators
        if (Segments.empty())
            {
            C->Status = Call::Blocked;
            continue;
            }

        for (auto &segment : Segments)
            {
            auto SegmentSlots = WA_Alg->assignSlots(C, segment);

            //There's no spectrum inside a transparent segment
            if (SegmentSlots.empty())
                {
                C->Status = Call::Blocked;
                Slots.clear();
                break;
                }

            Slots.insert(SegmentSlots.begin(), SegmentSlots.end());
            }

        if (C->Status != Call::Blocked)
            {
            break;
            }
        }

    if (C->Status == Call::Not_Evaluated)
        {
        C->Status = Call::Implemented;
        }

    return std::shared_ptr<Route>(new Route(Segments, Slots));
}
