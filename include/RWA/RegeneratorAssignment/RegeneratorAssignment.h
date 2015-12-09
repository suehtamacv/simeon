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

    RegeneratorAssignment(std::shared_ptr<Topology> T, std::vector<std::shared_ptr<ModulationScheme>> Schemes);

    std::shared_ptr<Topology> T;
    std::vector<std::shared_ptr<ModulationScheme>> ModulationSchemes;

    virtual bool assignRegenerators(Call C, std::shared_ptr<Route> R) = 0;
    unsigned int get_NumNeededRegenerators(Call C);

    bool isThereSpectrumAndOSNR(Call C,
                                std::shared_ptr<Route> R,
                                std::weak_ptr<Node> s,
                                std::weak_ptr<Node> x);
    ModulationScheme getMostEfficientScheme(Call C,
                                            std::shared_ptr<Route> R,
                                            std::weak_ptr<Node> s,
                                            std::weak_ptr<Node> x);
    TransparentSegment createTransparentSegment(Call C,
            std::shared_ptr<Route> R,
            std::weak_ptr<Node> s,
            std::weak_ptr<Node> r,
            unsigned int NumRegUsed);
};

#endif // REGENERATORASSIGNMENT_H
