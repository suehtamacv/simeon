#ifndef ROUTINGWAVELENGTHASSIGNMENT_H
#define ROUTINGWAVELENGTHASSIGNMENT_H

#include <memory>

#include <Calls/Call.h>
#include <Structure/Topology.h>
#include <RWA/Route.h>
#include <RWA/Routing/RoutingAlgorithm.h>
#include <RWA/WavelengthAssignment/WavelengthAssignmentAlgorithm.h>

class RoutingWavelengthAssignment {
  public:
    RoutingWavelengthAssignment(std::shared_ptr<RoutingAlgorithm>  R_Alg,
                                std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg,
                                std::shared_ptr<Topology> T);

    std::shared_ptr<RoutingAlgorithm> R_Alg;
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg;
    std::shared_ptr<Topology> T;

    std::shared_ptr<Route> routeCall(Call C);
};

#endif // ROUTINGWAVELENGTHASSIGNMENT_H
