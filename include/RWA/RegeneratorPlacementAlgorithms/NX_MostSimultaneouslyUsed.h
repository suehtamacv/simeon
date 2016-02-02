#ifndef NX_MOSTSIMULTANEOUSLYUSED_H
#define NX_MOSTSIMULTANEOUSLYUSED_H

#include "NX_RegeneratorPlacement.h"
#include <GeneralClasses/TransmissionBitrate.h>

class RoutingWavelengthAssignment;

class NX_MostSimultaneouslyUsed : public NX_RegeneratorPlacement
{
public:
    NX_MostSimultaneouslyUsed(std::shared_ptr<Topology> T,
                              std::shared_ptr<RoutingWavelengthAssignment> RWA,
                              double NetworkLoad,
                              long long unsigned NumCalls,
                              std::vector<TransmissionBitrate> Bitrates =
                                  TransmissionBitrate::DefaultBitrates);
    void placeRegenerators(unsigned N, unsigned X);

private:
    std::shared_ptr<RoutingWavelengthAssignment> RWA;
    double NetworkLoad;
    long long unsigned NumCalls;
    std::vector<TransmissionBitrate> Bitrates;

};

#endif // NX_MOSTSIMULTANEOUSLYUSED_H
