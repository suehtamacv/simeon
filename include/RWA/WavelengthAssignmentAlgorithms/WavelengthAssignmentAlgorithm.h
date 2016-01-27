#ifndef WAVELENGTHASSIGNMENTALGORITHM_H
#define WAVELENGTHASSIGNMENTALGORITHM_H

#include <map>
#include <boost/bimap.hpp>
#include <RWA/TransparentSegment.h>

class Call;
class Slot;
class Topology;

class WavelengthAssignmentAlgorithm
{
public:
#define WAVELENGTHASSIGNMENT_ALGORITHM \
    X(FF, "First Fit", "FF")

#define X(a,b,c) a,
    enum WavelengthAssignmentAlgorithms
    {
        WAVELENGTHASSIGNMENT_ALGORITHM
    };
#undef X

    typedef boost::bimap<WavelengthAssignmentAlgorithms, std::string>
    WavAssignAlgNameBimap;
    static WavAssignAlgNameBimap WavelengthAssignmentAlgorithmNames;
    typedef boost::bimap<WavelengthAssignmentAlgorithms, std::string>
    WavAssignAlgNicknameBimap;
    static WavAssignAlgNicknameBimap WavelengthAssignmentAlgorithmNicknames;

    WavelengthAssignmentAlgorithms WavAssAlgType;

    WavelengthAssignmentAlgorithm(std::shared_ptr<Topology> T, WavelengthAssignmentAlgorithms WavAssAlgType);

    virtual std::map<std::weak_ptr<Link>,
            std::vector<std::weak_ptr<Slot>>,
            std::owner_less<std::weak_ptr<Link>>>
            assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg) = 0;
    static WavelengthAssignmentAlgorithms define_WavelengthAssignmentAlgorithm();
    static std::shared_ptr<WavelengthAssignmentAlgorithm>
    create_WavelengthAssignmentAlgorithm(WavelengthAssignmentAlgorithms,
                                         std::shared_ptr<Topology>);
    virtual void load() = 0;
    virtual void save(std::string) = 0;

    std::shared_ptr<Topology> T;
};

#endif // WAVELENGTHASSIGNMENTALGORITHM_H
