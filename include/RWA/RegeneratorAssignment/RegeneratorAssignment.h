#ifndef REGENERATORASSIGNMENT_H
#define REGENERATORASSIGNMENT_H

#include <memory>
#include <Structure/Topology.h>
#include <Calls/Call.h>
#include <RWA/Route.h>

class RegeneratorAssignment {
  public:
    /**
     * @brief RegeneratorBitrate is the maximum bitrate that a single Regenerator
     * can regenerate. It's measured in bits per second.
     */
    constexpr static long double RegeneratorBitrate = 100E9;

    RegeneratorAssignment(std::shared_ptr<Topology> T);

    std::shared_ptr<Topology> T;

    virtual bool assignRegenerators(Call C, std::shared_ptr<Route> R) = 0;
    unsigned int get_NumNeededRegenerators(Call C);
};

#endif // REGENERATORASSIGNMENT_H
