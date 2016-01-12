#ifndef ROUTINGWAVELENGTHASSIGNMENT_H
#define ROUTINGWAVELENGTHASSIGNMENT_H

#include <vector>
#include <memory>
#include <Calls/Call.h>

class RoutingAlgorithm;
class WavelengthAssignmentAlgorithm;
class RegeneratorAssignmentAlgorithm;
class ModulationScheme;
class Topology;
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
     * @param WA_Alg is a pointer to the WavelengthAssignmentAlgorithm.
     * @param RA_Alg is a pointer to the RegeneratorAssignmentAlgorithm.
     * @param Schemes is a vector with the possible modulation schemes.
     * @param T is a pointer to the topology.
     */
    RoutingWavelengthAssignment(std::shared_ptr<RoutingAlgorithm>  R_Alg,
                                std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
                                std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg,
                                std::vector<ModulationScheme> Schemes,
                                std::shared_ptr<Topology> T);

    /**
     * @brief RoutingWavelengthAssignment is the constructor of a
     * RoutingWavelengthAssignment object, for a Transparent simulation.
     * @param R_Alg is a pointer to the RoutingAlgorithm.
     * @param WA_Alg is a pointer to the WavelengthAssignmentAlgorithm.
     * @param Schemes is a vector with the possible modulation schemes.
     * @param T is a pointer to the topology.
     */
    RoutingWavelengthAssignment(std::shared_ptr<RoutingAlgorithm>  R_Alg,
                                std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
                                std::vector<ModulationScheme> Schemes,
                                std::shared_ptr<Topology> T);

    /**
     * @brief R_Alg is a pointer to the RoutingAlgorithm.
     */
    std::shared_ptr<RoutingAlgorithm> R_Alg;
    /**
     * @brief WA_Alg is a pointer to the WavelengthAssignmentAlgorithm.
     */
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg;
    /**
     * @brief RA_Alg is a pointer to the RegeneratorAssignmentAlgorithm. If the
     * simulation is transparent, this pointer must be nullptr.
     */
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg;
    /**
     * @brief Schemes is a vector with the possible modulation schemes.
     */
    std::vector<ModulationScheme> Schemes;
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
};

#endif // ROUTINGWAVELENGTHASSIGNMENT_H
