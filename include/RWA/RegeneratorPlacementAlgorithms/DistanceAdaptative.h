#ifndef DISTANCEADAPTATIVE_H
#define DISTANCEADAPTATIVE_H

#include "RegeneratorPlacementAlgorithm.h"

class DistanceAdaptative : public RegeneratorPlacementAlgorithm
{
public:
    DistanceAdaptative(std::shared_ptr<Topology> T);
    void load();
    void placeRegenerators(unsigned NumTotalReg = 0, unsigned = 0);

private:
    static int DA_NumTotalRegenerators;
};

#endif // DISTANCEADAPTATIVE_H
