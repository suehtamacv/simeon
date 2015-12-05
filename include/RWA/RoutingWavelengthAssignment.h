#ifndef ROUTINGWAVELENGTHASSIGNMENT_H
#define ROUTINGWAVELENGTHASSIGNMENT_H

#include <memory>
#include <RWA/Routing/RoutingAlgorithm.h>
#include <RWA/WavelengthAssignment/WavelengthAssignmentAlgorithm.h>

class RoutingWavelengthAssignment {
  public:
    RoutingWavelengthAssignment(std::shared_ptr<RoutingAlgorithm>  R_Alg,
                                std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg);

    std::shared_ptr<RoutingAlgorithm> R_Alg;
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg;
};

#endif // ROUTINGWAVELENGTHASSIGNMENT_H
