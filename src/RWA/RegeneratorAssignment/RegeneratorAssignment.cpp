#include <RWA/RegeneratorAssignment/RegeneratorAssignment.h>
#include <cmath>
#include <algorithm>
#include <boost/assert.hpp>
#include <Structure/Link.h>

RegeneratorAssignment::RegeneratorAssignment(std::shared_ptr<Topology> T,
        std::vector<std::shared_ptr<ModulationScheme> > Schemes) :
    T(T), ModulationSchemes(Schemes) {

}

unsigned int RegeneratorAssignment::get_NumNeededRegenerators(Call C) {
    return ceil(C.Bitrate.get_Bitrate() / RegeneratorBitrate);
}

bool RegeneratorAssignment::isThereSpectrumAndOSNR(Call C,
        std::shared_ptr<Route> R,
        std::weak_ptr<Node> s,
        std::weak_ptr<Node> x) {

    Signal Sig;
    Sig = R->partial_bypass(Sig, s, x);

    for (auto scheme : ModulationSchemes) {
        //There's OSNR
        if (Sig.get_OSNR() > scheme->get_ThresholdOSNR(C.Bitrate)) {
            //There's spectrum
            if (R->get_MaxContigSlots(s, x) > scheme->get_NumSlots(C.Bitrate)) {
                return true;
            }
        }
    }

    return false;
}

ModulationScheme RegeneratorAssignment::getMostEfficientScheme(Call C,
        std::shared_ptr<Route> R,
        std::weak_ptr<Node> s,
        std::weak_ptr<Node> x) {

    Signal Sig;
    Sig = R->partial_bypass(Sig, s, x);

    std::sort(ModulationSchemes.rbegin(), ModulationSchemes.rend());

    for (auto scheme : ModulationSchemes) {
        //There's OSNR
        if (Sig.get_OSNR() > scheme->get_ThresholdOSNR(C.Bitrate)) {
            //There's spectrum
            if (R->get_MaxContigSlots(s, x) > scheme->get_NumSlots(C.Bitrate)) {
                return *scheme;
            }
        }
    }

    BOOST_ASSERT_MSG(false, "No Scheme can implement Call in Transparent Segment.");
}

TransparentSegment RegeneratorAssignment::createTransparentSegment(Call C,
        std::shared_ptr<Route> R,
        std::weak_ptr<Node> s,
        std::weak_ptr<Node> r,
        unsigned int NumRegUsed) {

    std::vector<std::weak_ptr<Link>> SegmentLinks;
    bool foundNode = false;

    for (auto link : R->Links) {
        if (link.lock()->Origin.lock() == s.lock()) {
            foundNode = true;
        } else if (link.lock()->Origin.lock() == r.lock()) {
            break;
        } else if (foundNode) {
            SegmentLinks.push_back(link);
        }
    }

    ModulationScheme Scheme = getMostEfficientScheme(C, R, s, r);

    return TransparentSegment(SegmentLinks, Scheme, NumRegUsed);
}
