#ifndef REGENERATORASSIGNMENTALGORITHM_H
#define REGENERATORASSIGNMENTALGORITHM_H

#include <memory>
#include <Structure/Topology.h>
#include <Calls/Call.h>
#include <RWA/Route.h>

class RegeneratorAssignmentAlgorithm {
  public:
    /**
     * @brief RegeneratorBitrate is the maximum bitrate that a single Regenerator
     * can regenerate. It's measured in bits per second.
     */
    constexpr static long double RegeneratorBitrate = 100E9;

    RegeneratorAssignmentAlgorithm(std::shared_ptr<Topology> T,
                                   std::vector<ModulationScheme> Schemes);

    std::shared_ptr<Topology> T;
    std::vector<ModulationScheme> ModulationSchemes;

    virtual std::vector<TransparentSegment> assignRegenerators(
        std::shared_ptr<Call> C,
        std::vector<std::weak_ptr<Link>> Links) = 0;
    unsigned int get_NumNeededRegenerators(std::shared_ptr<Call> C);

    bool isThereSpectrumAndOSNR(std::shared_ptr<Call> C,
                                std::vector<std::weak_ptr<Link>> Links,
                                std::weak_ptr<Node> start,
                                std::weak_ptr<Node> end);
    bool isThereSpectrumAndOSNR(std::shared_ptr<Call> C,
                                std::vector<std::weak_ptr<Link>> Links,
                                std::weak_ptr<Node> start,
                                std::weak_ptr<Node> end,
                                ModulationScheme scheme);
    ModulationScheme getMostEfficientScheme(std::shared_ptr<Call> C,
                                            std::vector<std::weak_ptr<Link>> SegmentLinks);
    TransparentSegment createTransparentSegment(std::shared_ptr<Call> C,
            std::vector<std::weak_ptr<Link>> Links,
            std::weak_ptr<Node> start,
            std::weak_ptr<Node> end,
            unsigned int NumRegUsed);
  private:
    std::vector<std::weak_ptr<Link>> segmentLinks(
                                      std::vector<std::weak_ptr<Link>>Links,
                                      std::weak_ptr<Node> start,
                                      std::weak_ptr<Node> end);
};

#endif // REGENERATORASSIGNMENTALGORITHM_H
