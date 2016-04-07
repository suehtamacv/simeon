#ifndef MOSTUSED_H
#define MOSTUSED_H

#include <RMSA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h>
#include <GeneralClasses/TransmissionBitrate.h>

class RoutingWavelengthAssignment;

namespace RP
{
/**
 * @brief The MostUsed class is the standard constructor for the Most Used RP
 * algorithm.
 *
 * It runs an opaque simulation, and computes how many regenerators were used on
 * each node. Then, it allocates regenerators on the N that were most used, and
 * puts X regenerators on each one.
 */
class MostUsed : public NX_RegeneratorPlacement
{
public:
    MostUsed(std::shared_ptr<Topology> T,
             std::shared_ptr<RoutingWavelengthAssignment> RMSA,
             double NetworkLoad,
             long long unsigned NumCalls = 1E6,
             std::vector<TransmissionBitrate> Bitrates = TransmissionBitrate::DefaultBitrates
            );

    void placeRegenerators(unsigned N, unsigned X);
    void load();

private:
    std::shared_ptr<RoutingWavelengthAssignment> RMSA;
    double NetworkLoad;
    long long unsigned NumCalls;
    std::vector<TransmissionBitrate> Bitrates;
};
}

#endif // MOSTUSED_H
