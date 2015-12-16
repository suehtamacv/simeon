#ifndef WAVELENGTHASSIGNMENTALGORITHM_H
#define WAVELENGTHASSIGNMENTALGORITHM_H

#include <map>
#include <Structure/Slot.h>
#include <Structure/Topology.h>
#include <RWA/TransparentSegment.h>

class Call;

class WavelengthAssignmentAlgorithm {
  public:
#define WAVELENGTHASSIGNMENT_ALGORITHM \
    X(FF, "First Fit", "FF")

#define X(a,b,c) a,
    enum WavelengthAssignmentAlgorithms {
        WAVELENGTHASSIGNMENT_ALGORITHM
    };
#undef X

    typedef boost::bimap<WavelengthAssignmentAlgorithms, std::string>
    WavAssignAlgNameBimap;
    static WavAssignAlgNameBimap WavelengthAssignmentAlgorithmNames;
    typedef boost::bimap<WavelengthAssignmentAlgorithms, std::string>
    WavAssignAlgNicknameBimap;
    static WavAssignAlgNicknameBimap WavelengthAssignmentAlgorithmNicknames;

    static WavelengthAssignmentAlgorithms load();

    WavelengthAssignmentAlgorithm(std::shared_ptr<Topology> T);

    virtual std::map<std::weak_ptr<Link>,
            std::vector<std::weak_ptr<Slot>>,
            std::owner_less<std::weak_ptr<Link>>>
            assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg) = 0;

    std::shared_ptr<Topology> T;
};

#endif // WAVELENGTHASSIGNMENTALGORITHM_H
