#ifndef REGENERATORASSIGNMENT_H
#define REGENERATORASSIGNMENT_H

#include <memory>
#include <Structure/Topology.h>
#include <Calls/Call.h>
#include <RWA/Route.h>

class RegeneratorAssignment {
  public:
    RegeneratorAssignment(std::shared_ptr<Topology> T);

    std::shared_ptr<Topology> T;

    virtual void assignRegenerators(Call C, std::shared_ptr<Route> R) = 0;
};

#endif // REGENERATORASSIGNMENT_H
