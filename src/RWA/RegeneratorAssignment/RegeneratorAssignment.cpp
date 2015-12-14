#include <RWA/RegeneratorAssignment/RegeneratorAssignment.h>
#include <cmath>
#include <algorithm>
#include <boost/assert.hpp>
#include <Structure/Link.h>

RegeneratorAssignment::RegeneratorAssignment(std::shared_ptr<Topology> T,
        std::vector<ModulationScheme> Schemes) :
    T(T), ModulationSchemes(Schemes) {

}

unsigned int RegeneratorAssignment::get_NumNeededRegenerators(
    std::shared_ptr<Call> C) {
    return ceil(C->Bitrate.get_Bitrate() / RegeneratorBitrate);
}

bool RegeneratorAssignment::isThereSpectrumAndOSNR(std::shared_ptr<Call> C,
        std::vector<std::weak_ptr<Link> > Links,
        std::weak_ptr<Node> start,
        std::weak_ptr<Node> end) {

    bool isThereScheme = false;

    for (auto scheme : ModulationSchemes) {
        isThereScheme |= isThereSpectrumAndOSNR(C, Links, start, end, scheme);

        if (isThereScheme) {
            break;
        }
    }

    return isThereScheme;
}

bool RegeneratorAssignment::isThereSpectrumAndOSNR(std::shared_ptr<Call> C,
        std::vector<std::weak_ptr<Link> > Links,
        std::weak_ptr<Node> start,
        std::weak_ptr<Node> end,
        ModulationScheme scheme) {

    TransparentSegment Segment(segmentLinks(Links, start, end), scheme, 0);
    Signal Sig = Segment.bypass(Signal());

    return ((Sig.get_OSNR() >= scheme.get_ThresholdOSNR(C->Bitrate)) &&
            (Segment.get_MaxContigSlots() >= scheme.get_NumSlots(C->Bitrate)));
}

ModulationScheme RegeneratorAssignment::getMostEfficientScheme(
    std::shared_ptr<Call> C,
    std::vector<std::weak_ptr<Link>> SegmentLinks) {

    TransparentSegment Segment(SegmentLinks, ModulationSchemes.front(), 0);
    Signal S = Segment.bypass(Signal());

    std::sort(ModulationSchemes.rbegin(), ModulationSchemes.rend());

    for (auto scheme : ModulationSchemes) {
        Segment.ModScheme = scheme;

        if (((S.get_OSNR() >= scheme.get_ThresholdOSNR(C->Bitrate))) &&
                ((Segment.get_MaxContigSlots() >= scheme.get_NumSlots(C->Bitrate)))) {
            return scheme;

        }
    }

    BOOST_ASSERT_MSG(false, "No Scheme can implement Call in Transparent Segment.");
    return ModulationSchemes.back();
}

TransparentSegment RegeneratorAssignment::createTransparentSegment(
    std::shared_ptr<Call> C,
    std::vector<std::weak_ptr<Link> > Links,
    std::weak_ptr<Node> start,
    std::weak_ptr<Node> end,
    unsigned int NumRegUsed) {

    std::vector<std::weak_ptr<Link>> SegmentLinks = segmentLinks(Links, start, end);

    return TransparentSegment(SegmentLinks,
                              getMostEfficientScheme(C, SegmentLinks),
                              NumRegUsed);
}

std::vector<std::weak_ptr<Link>> RegeneratorAssignment::segmentLinks(
                                  std::vector<std::weak_ptr<Link> > Links,
                                  std::weak_ptr<Node> start,
std::weak_ptr<Node> end) {

    std::vector<std::weak_ptr<Link>> SegmentLinks;
    bool foundNode = false;

    for (auto link : Links) {
        if (link.lock()->Origin.lock() == start.lock()) {
            SegmentLinks.push_back(link);
            foundNode = true;
            continue;
        } else if (foundNode && (link.lock()->Origin.lock() == end.lock())) {
            break;
        } else if (foundNode) {
            SegmentLinks.push_back(link);
            continue;
        }
    }

    return SegmentLinks;
}
