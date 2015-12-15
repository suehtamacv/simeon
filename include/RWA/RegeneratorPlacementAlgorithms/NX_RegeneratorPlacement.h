#ifndef NX_REGENERATORPLACEMENT_H
#define NX_REGENERATORPLACEMENT_H

#include <RWA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>

/**
 * @brief The NX_RegeneratorPlacement class is a type of RegeneratorPlacementAlgorithm.
 */
class NX_RegeneratorPlacement : public RegeneratorPlacementAlgorithm {
  public:
    /**
     * @brief NX_RegeneratorPlacement is the standard constructor.
     * @param T is a pointer to the Topology.
     */
    NX_RegeneratorPlacement(std::shared_ptr<Topology> T);

    /**
     * @brief placeRegenerators inserts the regenerators in the network.
     * @param N is the number of translucent nodes.
     * @param X is the number of regenerators per translucent node.
     */
    virtual void placeRegenerators(unsigned N, unsigned X) = 0;
};

#endif // NX_REGENERATORPLACEMENT_H
