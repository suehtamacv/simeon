#ifndef DISTANCEADAPTATIVE_H
#define DISTANCEADAPTATIVE_H

#include "RegeneratorPlacementAlgorithm.h"

namespace RP
{
/**
 * @brief The DistanceAdaptative class implements the Distance Adaptative RP algorithm.
 *
 * It distributes the regenerators proportionally to the length of the links
 * connected to each node.
 */
class DistanceAdaptative : public RegeneratorPlacementAlgorithm
{
public:
    DistanceAdaptative(std::shared_ptr<Topology> T);
    void load();
    void placeRegenerators(unsigned NumTotalReg = 0, unsigned = 0);

private:
    static int DA_NumTotalRegenerators;
};
}

#endif // DISTANCEADAPTATIVE_H
