#ifndef MOSTUSED_H
#define MOSTUSED_H

#include <RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h>
#include <GeneralClasses/TransmissionBitrate.h>

class RoutingWavelengthAssignment;

class MostUsed : public NX_RegeneratorPlacement
{
public:
    MostUsed(std::shared_ptr<Topology> T,
             std::shared_ptr<RoutingWavelengthAssignment> RWA,
             double NetworkLoad,
             long long unsigned NumCalls = 1E6,
             std::vector<TransmissionBitrate> Bitrates = TransmissionBitrate::DefaultBitrates
            );

    void placeRegenerators(unsigned N, unsigned X);
    void load();

private:
    std::shared_ptr<RoutingWavelengthAssignment> RWA;
    double NetworkLoad;
    long long unsigned NumCalls;
    std::vector<TransmissionBitrate> Bitrates;
};

#endif // MOSTUSED_H
