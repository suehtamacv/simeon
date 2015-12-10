#include <RWA/RoutingWavelengthAssignment.h>
#include <algorithm>
#include <GeneralClasses/ModulationScheme.h>
#include <RWA/Route.h>
#include <RWA/Routing/RoutingAlgorithm.h>
#include <RWA/WavelengthAssignment/WavelengthAssignmentAlgorithm.h>
#include <RWA/RegeneratorPlacement/RegeneratorPlacement.h>
#include <RWA/RegeneratorAssignment/RegeneratorAssignment.h>
#include <Structure/Topology.h>

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm> R_Alg,
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
    std::shared_ptr<RegeneratorAssignment> RA_Alg,
    std::vector<ModulationScheme> Schemes,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg), WA_Alg(WA_Alg), RA_Alg(RA_Alg), Schemes(Schemes), T(T) {

}

RoutingWavelengthAssignment::RoutingWavelengthAssignment(
    std::shared_ptr<RoutingAlgorithm>  R_Alg,
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
    std::vector<ModulationScheme> Schemes,
    std::shared_ptr<Topology> T) :
    R_Alg(R_Alg), WA_Alg(WA_Alg), Schemes(Schemes), T(T) {

    RA_Alg = nullptr;

}

std::shared_ptr<Route> RoutingWavelengthAssignment::routeCall(Call C) {

    std::vector<std::weak_ptr<Link>> Links;
    std::vector<TransparentSegment> Segments;
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;

    Links = R_Alg->route(C);

    if (RA_Alg == 0) {
        std::sort(Schemes.rbegin(), Schemes.rend());

        for (auto scheme : Schemes) {
            TransparentSegment Segment(Links, scheme, 0);
            Signal S;

            if (Segment.bypass(S).get_OSNR() > scheme.get_ThresholdOSNR(C.Bitrate)) {
                Segments.push_back(Segment);
                auto SegmentSlots = WA_Alg->assignSlots(C, Segment);
                Slots.insert(SegmentSlots.begin(), SegmentSlots.end());
                break;
            }
        }
    } else {
        Segments = RA_Alg->assignRegenerators(C, Links);

        for (auto segment : Segments) {
            auto SegmentSlots = WA_Alg->assignSlots(C, segment);
            Slots.insert(SegmentSlots.begin(), SegmentSlots.end());
        }
    }

    return std::shared_ptr<Route>(new Route(Segments, Slots));
}
