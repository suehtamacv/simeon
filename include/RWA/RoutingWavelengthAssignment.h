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

class RoutingWavelengthAssignment {
  public:
    RoutingWavelengthAssignment(std::shared_ptr<RoutingAlgorithm>  R_Alg,
                                std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
                                std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg,
                                std::vector<ModulationScheme> Schemes,
                                std::shared_ptr<Topology> T);

    RoutingWavelengthAssignment(std::shared_ptr<RoutingAlgorithm>  R_Alg,
                                std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
                                std::vector<ModulationScheme> Schemes,
                                std::shared_ptr<Topology> T);

    std::shared_ptr<RoutingAlgorithm> R_Alg;
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg;
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg;
    std::vector<ModulationScheme> Schemes;
    std::shared_ptr<Topology> T;

    std::shared_ptr<Route> routeCall(std::shared_ptr<Call> C);
};

#endif // ROUTINGWAVELENGTHASSIGNMENT_H
