#ifndef EMPTY_REGENERATORPLACEMENTALGORITHM_H
#define EMPTY_REGENERATORPLACEMENTALGORITHM_H

#include <RWA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>

class Empty_RegeneratorPlacementAlgorithm : public RegeneratorPlacementAlgorithm
{
public:
    Empty_RegeneratorPlacementAlgorithm(std::shared_ptr<Topology> T);

    void placeRegenerators(unsigned, unsigned);
    void load();
};

#endif // EMPTY_REGENERATORPLACEMENTALGORITHM_H
