#ifndef SPECTRUMASSIGNMENTALGORITHM_H
#define SPECTRUMASSIGNMENTALGORITHM_H

#include <map>
#include <boost/bimap.hpp>
#include <RMSA/TransparentSegment.h>

class Call;
class Slot;
class Topology;

typedef std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>, std::owner_less<std::weak_ptr<Link>>>
        mapSlots;

namespace RMSA
{
//! Contains the spectrum assignment algorithms.
namespace SA
{
/**
 * @brief The SpectrumAssignmentAlgorithm class represents a spectrum assignment
 * algorithm.
 */
class SpectrumAssignmentAlgorithm
{
public:
#define SPECTRUMASSIGNMENT_ALGORITHM \
    X(BF, "Best Fit", "BF", BestFit) \
    X(EF, "Exact Fit", "EF", ExactFit) \
    X(FF, "First Fit", "FF", FirstFit) \
    X(LU, "Least Used", "LF", LeastUsed) \
    X(MU, "Most Used", "MU", MostUsed) \
    X(RF, "Random Fit", "RF", RandomFit)

#define X(a,b,c,d) a,
    enum SpectrumAssignmentAlgorithms
    {
        SPECTRUMASSIGNMENT_ALGORITHM
    };
#undef X

    typedef boost::bimap<SpectrumAssignmentAlgorithms, std::string>
    SpecAssignAlgNameBimap;
    static SpecAssignAlgNameBimap SpectrumAssignmentAlgorithmNames;
    typedef boost::bimap<SpectrumAssignmentAlgorithms, std::string>
    SpecAssignAlgNicknameBimap;
    static SpecAssignAlgNicknameBimap SpectrumAssignmentAlgorithmNicknames;

    SpectrumAssignmentAlgorithms SpecAssAlgType;
    SpectrumAssignmentAlgorithm (std::shared_ptr<Topology> T,
                                 SpectrumAssignmentAlgorithms SpecAssAlgType);

    /**
     * @brief assignSlots assigns the slots on the transparent segment.
     * @param C is the Call where the slots will be assigned.
     * @param Seg is the transparent segment will be assigned.
     * @return a map that associates, to each pointer to a Link, a vector containing
     * the slots used by this Call on the link.
     */
    virtual mapSlots assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg) = 0;
    /**
     * @brief define_SpectrumAssignmentAlgorithm asks the user to define a spectrum
     * assignment algorithm.
     * @return the chosen spectrum assignment algorithm.
     */
    static SpectrumAssignmentAlgorithms define_SpectrumAssignmentAlgorithm();
    /**
     * @brief create_SpectrumAssignmentAlgorithm creates a spectrum assignment
     * algorithm.
     * @return a pointer to the created spectrum assignment algorithm.
     */
    static std::shared_ptr<SpectrumAssignmentAlgorithm>
    create_SpectrumAssignmentAlgorithm(SpectrumAssignmentAlgorithms,
                                       std::shared_ptr<Topology>);
    /**
     * @brief load loads the parameters required to run the SA algorithm.
     */
    virtual void load() = 0;
    /**
     * @brief save saves the loaded parameters on a file.
     */
    virtual void save(std::string) = 0;

    std::shared_ptr<Topology> T;
};
}
}

#endif // SPECTRUMASSIGNMENTALGORITHM_H
