#ifndef REGENERATORPLACEMENTALGORITHM_H
#define REGENERATORPLACEMENTALGORITHM_H

#include <Structure/Topology.h>
#include <boost/bimap.hpp>

/**
 * @brief The RegeneratorPlacementAlgorithm class decides how to insert the
 * regenerators over the network
 */
class RegeneratorPlacementAlgorithm {
  public:
#define REGPLACEMENT_ALGORITHMS \
    X(MSU, "Most Simultaneously Used", "MSU") \
    X(MU, "Most Used", "MU") \
    X(NDF, "Nodal Degree First", "NDF")


#define X(a,b,c) a,
    enum RegeneratorPlacementAlgorithms {
        REGPLACEMENT_ALGORITHMS
    };
#undef X

    typedef boost::bimap<RegeneratorPlacementAlgorithms, std::string>
    RegPlaceNameBimap;
    static RegPlaceNameBimap RegeneratorPlacementNames;
    typedef boost::bimap<RegeneratorPlacementAlgorithms, std::string>
    RegPlaceNicknameBimap;
    static RegPlaceNicknameBimap RegeneratorPlacementNicknames;

    /**
     * @brief RegeneratorPlacementAlgorithm is the standard constructor.
     * @param T is a pointer to the Topology.
     */
    RegeneratorPlacementAlgorithm(std::shared_ptr<Topology> T);
    /**
     * @brief T is a pointer to the Topology.
     */
    std::shared_ptr<Topology> T;
    /**
     * @brief placeRegenerators places the regenerators over the network.
     */
    virtual void placeRegenerators(unsigned, unsigned) = 0;

    RegeneratorPlacementAlgorithms define_RegeneratorPlacementAlgorithm();
};

#endif // REGENERATORPLACEMENTALGORITHM_H
