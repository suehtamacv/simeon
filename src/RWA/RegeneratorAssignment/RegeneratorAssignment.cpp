#include <RWA/RegeneratorAssignment/RegeneratorAssignment.h>
#include <cmath>
#include <algorithm>
#include <boost/assert.hpp>
#include <Structure/Link.h>

RegeneratorAssignment::RegeneratorAssignment(std::shared_ptr<Topology> T,
        std::vector<std::shared_ptr<ModulationScheme> > Schemes) :
    T(T), ModulationSchemes(Schemes) {

}

unsigned int RegeneratorAssignment::get_NumNeededRegenerators(std::shared_ptr<Call> C) {
    return ceil(C->Bitrate.get_Bitrate() / RegeneratorBitrate);
}

bool RegeneratorAssignment::isThereSpectrumAndOSNR(std::shared_ptr<Call> C,
        std::vector<std::weak_ptr<Link> > Links,
        std::weak_ptr<Node> s,
        std::weak_ptr<Node> x) {

    std::vector<std::weak_ptr<Link>> SegmentLinks;
    bool foundNode = false;

    for (auto link : Links) {
        if (link.lock()->Origin.lock() == s.lock()) {
            foundNode = true;
        } else if (link.lock()->Origin.lock() == x.lock()) {
            break;
        } else if (!foundNode) {
            continue;
        }

        SegmentLinks.push_back(link);
    }

    Signal Sig;
    TransparentSegment Segment(SegmentLinks, *ModulationSchemes.front(), 0);
    Sig = Segment.bypass(Sig);

    for (auto scheme : ModulationSchemes) {
        //There's OSNR
        if (Sig.get_OSNR() > scheme->get_ThresholdOSNR(C->Bitrate)) {
            //There's spectrum
            if (Segment.get_MaxContigSlots() > scheme->get_NumSlots(C->Bitrate)) {
                return true;
            }
        }
    }

    return false;
}

ModulationScheme RegeneratorAssignment::getMostEfficientScheme(std::shared_ptr<Call> C,
        std::vector<std::weak_ptr<Link> > Links,
        std::weak_ptr<Node> s,
        std::weak_ptr<Node> x) {

    std::vector<std::weak_ptr<Link>> SegmentLinks;
    bool foundNode = false;

    for (auto link : Links) {
        if (link.lock()->Origin.lock() == s.lock()) {
            foundNode = true;
        } else if (link.lock()->Origin.lock() == x.lock()) {
            break;
        } else if (!foundNode) {
            continue;
        }

        SegmentLinks.push_back(link);
    }

    TransparentSegment Segment(SegmentLinks, *ModulationSchemes.front(), 0);
    Signal Sig;
    Sig = Segment.bypass(Sig);

    std::sort(ModulationSchemes.rbegin(), ModulationSchemes.rend());

    for (auto scheme : ModulationSchemes) {
        //There's OSNR
        if (Sig.get_OSNR() > scheme->get_ThresholdOSNR(C->Bitrate)) {
            //There's spectrum
            if (Segment.get_MaxContigSlots() > scheme->get_NumSlots(C->Bitrate)) {
                return *scheme;
            }
        }
    }

    BOOST_ASSERT_MSG(false, "No Scheme can implement Call in Transparent Segment.");
    return *(ModulationSchemes.back());
}

TransparentSegment RegeneratorAssignment::createTransparentSegment(std::shared_ptr<Call> C,
        std::vector<std::weak_ptr<Link> > Links,
        std::weak_ptr<Node> s,
        std::weak_ptr<Node> r,
        unsigned int NumRegUsed) {

    std::vector<std::weak_ptr<Link>> SegmentLinks;
    bool foundNode = false;

    for (auto link : Links) {
        if (link.lock()->Origin.lock() == s.lock()) {
            foundNode = true;
        } else if (link.lock()->Origin.lock() == r.lock()) {
            break;
        } else if (foundNode) {
            SegmentLinks.push_back(link);
        }
    }

    ModulationScheme Scheme = getMostEfficientScheme(C, Links, s, r);

    return TransparentSegment(SegmentLinks, Scheme, NumRegUsed);
}
