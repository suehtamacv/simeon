#ifndef NX_MOSTSIMULTANEOUSLYUSED_H
#define NX_MOSTSIMULTANEOUSLYUSED_H

#include "NX_RegeneratorPlacement.h"
#include <GeneralClasses/TransmissionBitrate.h>

namespace RMSA
{
class RoutingWavelengthAssignment;

namespace RP
{
/**
 * @brief The NX_MostSimultaneouslyUsed class is a variant of the MostSimultaneouslyUsed
 * RP algorithm that is NX.
 */
class NX_MostSimultaneouslyUsed : public NX_RegeneratorPlacement
{
public:
    /**
     * @brief NX_MostSimultaneouslyUsed is the standard constructor for the
     * NX_MostSimultaneouslyUsed RP algorithm.
     */
    NX_MostSimultaneouslyUsed(std::shared_ptr<Topology> T,
                              std::shared_ptr<RoutingWavelengthAssignment> RMSA,
                              double NetworkLoad,
                              long long unsigned NumCalls,
                              std::vector<TransmissionBitrate> Bitrates =
                                  TransmissionBitrate::DefaultBitrates);

    void placeRegenerators(unsigned N, unsigned X);
    void load();

private:
    std::shared_ptr<RoutingWavelengthAssignment> RMSA;
    double NetworkLoad;
    long long unsigned NumCalls;
    std::vector<TransmissionBitrate> Bitrates;

};
}
}

#endif // NX_MOSTSIMULTANEOUSLYUSED_H
