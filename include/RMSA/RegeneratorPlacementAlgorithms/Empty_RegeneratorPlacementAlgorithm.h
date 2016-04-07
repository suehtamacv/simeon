#ifndef EMPTY_REGENERATORPLACEMENTALGORITHM_H
#define EMPTY_REGENERATORPLACEMENTALGORITHM_H

#include <RMSA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>

namespace RP
{
/**
 * @brief The Empty_RegeneratorPlacementAlgorithm class is a dummy RP algorithm.
 *
 * Use this when the regenerators were already set directly through the topology.
 * This RP algorithm won't mess with it.
 */
class Empty_RegeneratorPlacementAlgorithm : public RegeneratorPlacementAlgorithm
{
public:
    Empty_RegeneratorPlacementAlgorithm(std::shared_ptr<Topology> T);

    void placeRegenerators(unsigned, unsigned);
    void load();
};
}

#endif // EMPTY_REGENERATORPLACEMENTALGORITHM_H
