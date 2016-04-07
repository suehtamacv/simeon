#ifndef NODALDEGREEFIRST_H
#define NODALDEGREEFIRST_H

#include <RMSA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h>

namespace RP
{
/**
 * @brief The NodalDegreeFirst class implements the Nodal Degree First (NDF)
 * regenerator placement algorithm.
 */
class NodalDegreeFirst : public NX_RegeneratorPlacement
{
public:
    /**
     * @brief NodalDegreeFirst is the standard constructor.
     * @param T is a pointer to the Topology.
     */
    NodalDegreeFirst(std::shared_ptr<Topology> T);

    void placeRegenerators(unsigned N, unsigned X);
    void load();
};
}

#endif // NODALDEGREEFIRST_H
