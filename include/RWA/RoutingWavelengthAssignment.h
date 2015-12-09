#ifndef ROUTINGWAVELENGTHASSIGNMENT_H
#define ROUTINGWAVELENGTHASSIGNMENT_H

#include <memory>
#include <Calls/Call.h>
#include <ModulationSchemes/ModulationScheme.h>
#include <Structure/Topology.h>
#include <RWA/Route.h>
#include <RWA/Routing/RoutingAlgorithm.h>
#include <RWA/WavelengthAssignment/WavelengthAssignmentAlgorithm.h>
#include <RWA/RegeneratorPlacement/RegeneratorPlacement.h>
#include <RWA/RegeneratorAssignment/RegeneratorAssignment.h>

class RoutingWavelengthAssignment {
  public:
    RoutingWavelengthAssignment(std::shared_ptr<RoutingAlgorithm>  R_Alg,
                                std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
                                std::shared_ptr<RegeneratorPlacement> RP_Alg,
                                std::shared_ptr<RegeneratorAssignment> RA_Alg,
                                std::vector<ModulationScheme> Schemes,
                                std::shared_ptr<Topology> T);

    RoutingWavelengthAssignment(std::shared_ptr<RoutingAlgorithm>  R_Alg,
                                std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
                                std::vector<ModulationScheme> Schemes,
                                std::shared_ptr<Topology> T);

    std::shared_ptr<RoutingAlgorithm> R_Alg;
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg;
    std::shared_ptr<RegeneratorPlacement> RP_Alg;
    std::shared_ptr<RegeneratorAssignment> RA_Alg;
    std::vector<ModulationScheme> Schemes;
    std::shared_ptr<Topology> T;

    std::shared_ptr<Route> routeCall(Call C);
};

#endif // ROUTINGWAVELENGTHASSIGNMENT_H
