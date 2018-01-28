#ifndef ROUTINGWAVELENGTHASSIGNMENT_H
#define ROUTINGWAVELENGTHASSIGNMENT_H

#include <vector>
#include <memory>
#include <Calls/Call.h>

class ModulationScheme;
class Topology;

extern bool considerAseNoise;
extern bool considerFilterImperfection;

//! Routing, Modulation and Spectrum Assignment Algorithms.
namespace RMSA
{

namespace ROUT
{
class RoutingAlgorithm;
}
namespace SA
{
class SpectrumAssignmentAlgorithm;
}
namespace RA
{
class RegeneratorAssignmentAlgorithm;
}
class Route;

/**
 * @brief The RoutingWavelengthAssignment class is a container to the routing,
 * wavelength assignment, regenerator assignment and regenerator placement
 * operations that a call must endure before its implementation.
 */
class RoutingWavelengthAssignment
{
public:
    /**
     * @brief RoutingWavelengthAssignment is the constructor of a
     * RoutingWavelengthAssignment object, for a Translucent or Opaque simulation.
     * @param R_Alg is a pointer to the RoutingAlgorithm.
     * @param WA_Alg is a pointer to the SpectrumAssignmentAlgorithm.
     * @param RA_Alg is a pointer to the RegeneratorAssignmentAlgorithm.
     * @param Schemes is a set with the possible modulation schemes.
     * @param T is a pointer to the topology.
     */
    RoutingWavelengthAssignment(std::shared_ptr<ROUT::RoutingAlgorithm> R_Alg,
                                std::shared_ptr<SA::SpectrumAssignmentAlgorithm> WA_Alg,
                                std::shared_ptr<RA::RegeneratorAssignmentAlgorithm> RA_Alg,
                                std::set<ModulationScheme> Schemes,
                                std::shared_ptr<Topology> T);

    /**
     * @brief RoutingWavelengthAssignment is the constructor of a
     * RoutingWavelengthAssignment object, for a Transparent simulation.
     * @param R_Alg is a pointer to the RoutingAlgorithm.
     * @param WA_Alg is a pointer to the SpectrumAssignmentAlgorithm.
     * @param Schemes is a set with the possible modulation schemes.
     * @param T is a pointer to the topology.
     */
    RoutingWavelengthAssignment(std::shared_ptr<ROUT::RoutingAlgorithm> R_Alg,
                                std::shared_ptr<SA::SpectrumAssignmentAlgorithm> WA_Alg,
                                std::set<ModulationScheme> Schemes,
                                std::shared_ptr<Topology> T);

    /**
     * @brief R_Alg is a pointer to the RoutingAlgorithm.
     */
    std::shared_ptr<ROUT::RoutingAlgorithm> R_Alg;
    /**
     * @brief WA_Alg is a pointer to the SpectrumAssignmentAlgorithm.
     */
    std::shared_ptr<SA::SpectrumAssignmentAlgorithm> WA_Alg;
    /**
     * @brief RA_Alg is a pointer to the RegeneratorAssignmentAlgorithm. If the
     * simulation is transparent, this pointer must be nullptr.
     */
    std::shared_ptr<RA::RegeneratorAssignmentAlgorithm> RA_Alg;
    /**
     * @brief Schemes is a vector with the possible modulation schemes.
     */
    std::set<ModulationScheme> Schemes;
    /**
     * @brief T is a pointer to the topology.
     */
    std::shared_ptr<Topology> T;

    /**
     * @brief routeCall, given a Call C, operates over it, calling all the RWA
     * algorithms, in order to find a route.
     * @param C is the call being routed.
     * @return the route found for the call, or maybe nullptr if it's impossible
     * to implement the Call.
     */
    std::shared_ptr<Route> routeCall(std::shared_ptr<Call> C);

protected:
    std::shared_ptr<Route> routeCall_Transparent(std::shared_ptr<Call> C);
    std::shared_ptr<Route> routeCall_Translucent(std::shared_ptr<Call> C);
};
}

#endif // ROUTINGWAVELENGTHASSIGNMENT_H
