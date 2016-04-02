#ifndef SPECTRUMASSIGNMENTALGORITHM_H
#define SPECTRUMASSIGNMENTALGORITHM_H

#include <map>
#include <boost/bimap.hpp>
#include <RMSA/TransparentSegment.h>

class Call;
class Slot;
class Topology;

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
    SpectrumAssignmentAlgorithm (std::shared_ptr<Topology> T, SpectrumAssignmentAlgorithms SpecAssAlgType);

    virtual std::map<std::weak_ptr<Link>,
            std::vector<std::weak_ptr<Slot>>,
            std::owner_less<std::weak_ptr<Link>>>
            assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg) = 0;
    static SpectrumAssignmentAlgorithms define_SpectrumAssignmentAlgorithm();
    static std::shared_ptr<SpectrumAssignmentAlgorithm>
    create_SpectrumAssignmentAlgorithm(SpectrumAssignmentAlgorithms,
                                         std::shared_ptr<Topology>);
    virtual void load() = 0;
    virtual void save(std::string) = 0;

    std::shared_ptr<Topology> T;
};
}
#endif // SPECTRUMASSIGNMENTALGORITHM_H
