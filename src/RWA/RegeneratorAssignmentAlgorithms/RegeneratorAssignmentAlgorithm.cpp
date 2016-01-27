#include <RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>
#include <RWA/RegeneratorAssignmentAlgorithms.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <boost/assert.hpp>
#include <boost/assign.hpp>
#include <Structure/Link.h>
#include <Calls/Call.h>
#include <RWA/TransparentSegment.h>

RegeneratorAssignmentAlgorithm::RegAssignNameBimap
RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNames =
    boost::assign::list_of<RegeneratorAssignmentAlgorithm::RegAssignNameBimap::relation>
#define X(a,b,c) (a,b)
    REGASSIGNMENT_ALGORITHMS
#undef X
    ;

RegeneratorAssignmentAlgorithm::RegAssignNicknameBimap
RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames =
    boost::assign::list_of<RegeneratorAssignmentAlgorithm::RegAssignNameBimap::relation>
#define X(a,b,c) (a,c)
    REGASSIGNMENT_ALGORITHMS
#undef X
#undef REGASSIGNMENT_ALGORITHMS
    ;

RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithm(
    std::shared_ptr<Topology> T,
    RegeneratorAssignmentAlgorithms RegAssAlgType,
    std::vector<ModulationScheme> &Schemes) :
    T(T), ModulationSchemes(Schemes), RegAssAlgType(RegAssAlgType)
{

}

unsigned int RegeneratorAssignmentAlgorithm::get_NumNeededRegenerators(
    std::shared_ptr<Call> C)
{
    return ceil(C->Bitrate.get_Bitrate() / RegeneratorBitrate);
}

bool RegeneratorAssignmentAlgorithm::isThereSpectrumAndOSNR(
    std::shared_ptr<Call> C,
    std::vector<std::weak_ptr<Link>> &Links,
    std::weak_ptr<Node> start,
    std::weak_ptr<Node> end)
{

    bool isThereScheme = false;

    for (auto &scheme : ModulationSchemes)
        {
        isThereScheme |= isThereSpectrumAndOSNR(C, Links, start, end, scheme);

        if (isThereScheme)
            {
            break;
            }
        }

    return isThereScheme;
}

bool RegeneratorAssignmentAlgorithm::isThereSpectrumAndOSNR(
    std::shared_ptr<Call> C,
    std::vector<std::weak_ptr<Link> > Links,
    std::weak_ptr<Node> start,
    std::weak_ptr<Node> end,
    ModulationScheme scheme)
{

    TransparentSegment Segment(segmentLinks(Links, start, end), scheme, 0);
    Signal Sig = Segment.bypass(Signal());

    return ((Sig.get_OSNR() >= scheme.get_ThresholdOSNR(C->Bitrate)) &&
            (Segment.get_MaxContigSlots() >= scheme.get_NumSlots(C->Bitrate)));
}

ModulationScheme RegeneratorAssignmentAlgorithm::getMostEfficientScheme(
    std::shared_ptr<Call> C,
    std::vector<std::weak_ptr<Link>> SegmentLinks)
{

    TransparentSegment Segment(SegmentLinks, ModulationSchemes.front(), 0);
    Signal S = Segment.bypass(Signal());

    std::sort(ModulationSchemes.rbegin(), ModulationSchemes.rend());

    for (auto &scheme : ModulationSchemes)
        {
        Segment.ModScheme = scheme;

        if (((S.get_OSNR() >= scheme.get_ThresholdOSNR(C->Bitrate))) &&
                ((Segment.get_MaxContigSlots() >= scheme.get_NumSlots(C->Bitrate))))
            {
            return scheme;

            }
        }

    BOOST_ASSERT_MSG(false, "No Scheme can implement Call in Transparent Segment.");
    return ModulationSchemes.back();
}

TransparentSegment RegeneratorAssignmentAlgorithm::createTransparentSegment(
    std::shared_ptr<Call> C,
    std::vector<std::weak_ptr<Link> > Links,
    std::weak_ptr<Node> start,
    std::weak_ptr<Node> end,
    unsigned int NumRegUsed)
{

    std::vector<std::weak_ptr<Link>> SegmentLinks = segmentLinks(Links, start, end);

    return TransparentSegment(SegmentLinks,
                              getMostEfficientScheme(C, SegmentLinks),
                              NumRegUsed);
}

std::vector<std::weak_ptr<Link>> RegeneratorAssignmentAlgorithm::segmentLinks(
                                  std::vector<std::weak_ptr<Link> > Links,
                                  std::weak_ptr<Node> start,
                                  std::weak_ptr<Node> end)
{

    std::vector<std::weak_ptr<Link>> SegmentLinks;
    bool foundNode = false;

    for (auto &link : Links)
        {
        if (link.lock()->Origin.lock() == start.lock())
            {
            SegmentLinks.push_back(link);
            foundNode = true;
            continue;
            }
        else if (foundNode && (link.lock()->Origin.lock() == end.lock()))
            {
            break;
            }
        else if (foundNode)
            {
            SegmentLinks.push_back(link);
            continue;
            }
        }

    return SegmentLinks;
}

RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
RegeneratorAssignmentAlgorithm::define_RegeneratorAssignmentAlgorithm()
{
    std::cout << std::endl << "-> Choose a regenerator assignment algorithm."
              << std::endl;

    do
        {
        for (auto &rassign : RegeneratorAssignmentNames.left)
            {
            std::cout << "(" << rassign.first << ")\t" << rassign.second << std::endl;
            }

        int RegAssign_Alg;
        std::cin >> RegAssign_Alg;

        if (std::cin.fail() || RegeneratorAssignmentNames.left.count
                ((RegeneratorAssignmentAlgorithms) RegAssign_Alg) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid regenerator assignment algorithm." << std::endl;
            std::cout << std::endl << "-> Choose a regenerator assignment algorithm."
                      << std::endl;
            }
        else
            {
            return (RegeneratorAssignmentAlgorithms) RegAssign_Alg;
            }
        }
    while (1);

    return (RegeneratorAssignmentAlgorithms) - 1;
}

std::shared_ptr<RegeneratorAssignmentAlgorithm>
RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
    RegeneratorAssignmentAlgorithms Algorithm, std::shared_ptr<Topology> T)
{
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg;

    switch (Algorithm)
        {
        case FLR:
            RA_Alg = std::shared_ptr<RegeneratorAssignmentAlgorithm>(new FirstLongestReach(
                         T, ModulationScheme::DefaultSchemes));
            break;

        case FNS:
            RA_Alg = std::shared_ptr<RegeneratorAssignmentAlgorithm>
                     (new FirstNarrowestSpectrum(T, ModulationScheme::DefaultSchemes));
            break;
        }

    RA_Alg->load();
    return RA_Alg;
}

void RegeneratorAssignmentAlgorithm::save(std::string SimConfigFileName)
{
    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << "  RegeneratorAssignmentAlgorithm = " <<
                  RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames.left.at(
                      RegAssAlgType) << std::endl;
}
