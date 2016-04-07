#ifndef REGENERATORPLACEMENTALGORITHM_H
#define REGENERATORPLACEMENTALGORITHM_H

#include <boost/bimap.hpp>
#include <iostream>

extern bool considerAseNoise;
extern bool considerFilterImperfection;

class Topology;

namespace RMSA
{
class RoutingWavelengthAssignment;

//! Contains the Regenerator Placement Algorithms.
namespace RP
{
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
    X(SQP_Var, "Signal Quality Prediction (Variants)", "SQP_Var" ) \
    X(Empty, "Empty RP Algorithm", "Empty") //X Macros

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

    /**
     * @brief isNXAlgorithm is true iff the RP algorithm is NX, i.e., it allocates
     * N translucent nodes, putting X regenerators on each one.
     */
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

    /**
     * @brief define_RegeneratorPlacementAlgorithm asks the user to define the
     * RP algorithm.
     * @return the chosen RP algorithm.
     */
    static RegeneratorPlacementAlgorithms define_RegeneratorPlacementAlgorithm();
    /**
     * @brief create_RegeneratorPlacementAlgorithm creates a new RP algorithm.
     * @param RMSA is the RoutingWavelengthAssignment object required to run a
     * network simulation on the RP algorithms that require one.
     * @param OptimizationLoad is the Load where the opaque simulation will run.
     * @param NumCalls is the number of calls that will be executed by the RP
     * algorithm optimization.
     * @param runLoad is true iff this function is expected to run the load()
     * function of the RP algorithm.
     * @return the created RP algorithm.
     */
    static std::shared_ptr<RegeneratorPlacementAlgorithm>
    create_RegeneratorPlacementAlgorithm(RegeneratorPlacementAlgorithms,
                                         std::shared_ptr<Topology>,
                                         std::shared_ptr<RoutingWavelengthAssignment> RMSA,
                                         double OptimizationLoad,
                                         long long NumCalls,
                                         bool runLoad = true);
    /**
     * @brief load loads required parameters to the RP algorithm.
     */
    virtual void load() = 0;
    /**
     * @brief save saves the loaded parameters on a file.
     */
    static void save(std::string, RegeneratorPlacementAlgorithms);
};
}
}

#endif // REGENERATORPLACEMENTALGORITHM_H
