#ifndef REGENERATORPLACEMENTALGORITHM_H
#define REGENERATORPLACEMENTALGORITHM_H

#include <Structure/Topology.h>

/**
 * @brief The RegeneratorPlacementAlgorithm class decides how to insert the
 * regenerators over the network
 */
class RegeneratorPlacementAlgorithm {
  public:
    /**
     * @brief RegeneratorPlacementAlgorithm is the standard constructor.
     * @param T is a pointer to the Topology.
     */
    RegeneratorPlacementAlgorithm(std::shared_ptr<Topology> T);
    /**
     * @brief T is a pointer to the Topology.
     */
    std::shared_ptr<Topology> T;
    /**
     * @brief placeRegenerators places the regenerators over the network.
     */
    virtual void placeRegenerators(unsigned, unsigned) = 0;
};

#endif // REGENERATORPLACEMENTALGORITHM_H
