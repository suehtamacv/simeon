#ifndef REGENERATORPLACEMENTALGORITHM_H
#define REGENERATORPLACEMENTALGORITHM_H

#include <boost/bimap.hpp>
#include <iostream>

extern bool considerAseNoise;
extern bool considerFilterImperfection;

class RoutingWavelengthAssignment;
class Topology;

/**
 * @brief The RegeneratorPlacementAlgorithm class decides how to insert the
 * regenerators over the network
 */
class RegeneratorPlacementAlgorithm
{
public:
#define REGPLACEMENT_ALGORITHMS \
    X(DA, "Distance Adaptative", "DA") \
    X(MSU, "Most Simultaneously Used", "MSU") \
    X(NX_MSU, "Most Simultaneously Used (NX Variant)", "NX_MSU") \
    X(MU, "Most Used", "MU") \
    X(NDF, "Nodal Degree First", "NDF") \
    X(SQP, "Signal Quality Prediction", "SQP") \
    X(SQP_Var, "Signal Quality Prediction (Variants)", "SQP_Var" ) //X Macros


#define X(a,b,c) a,
    enum RegeneratorPlacementAlgorithms
    {
        REGPLACEMENT_ALGORITHMS
    };
#undef X

    typedef boost::bimap<RegeneratorPlacementAlgorithms, std::string>
    RegPlaceNameBimap;
    static RegPlaceNameBimap RegeneratorPlacementNames;
    typedef boost::bimap<RegeneratorPlacementAlgorithms, std::string>
    RegPlaceNicknameBimap;
    static RegPlaceNicknameBimap RegeneratorPlacementNicknames;

    bool isNXAlgorithm;

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
    virtual void placeRegenerators(unsigned = 0, unsigned = 0) = 0;

    static RegeneratorPlacementAlgorithms define_RegeneratorPlacementAlgorithm();
    static std::shared_ptr<RegeneratorPlacementAlgorithm>
    create_RegeneratorPlacementAlgorithm(RegeneratorPlacementAlgorithms,
                                         std::shared_ptr<Topology>,
                                         std::shared_ptr<RoutingWavelengthAssignment> RWA,
                                         double OptimizationLoad,
                                         long long NumCalls,
                                         bool runLoad = true);
    virtual void load() = 0;
    static void save(std::string, RegeneratorPlacementAlgorithms);
};

#endif // REGENERATORPLACEMENTALGORITHM_H
