#ifndef MOSTUSED_H
#define MOSTUSED_H

#include <RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h>
#include <GeneralClasses/TransmissionBitrate.h>

class RoutingWavelengthAssignment;

class MostUsed : public NX_RegeneratorPlacement {
  public:
    MostUsed(std::shared_ptr<Topology> T,
             std::shared_ptr<RoutingWavelengthAssignment> RWA,
             long double NetworkLoad,
             long long unsigned NumCalls,
             std::vector<TransmissionBitrate> Bitrates
            );

    void placeRegenerators(unsigned N, unsigned X);

  private:
    std::shared_ptr<RoutingWavelengthAssignment> RWA;
    long double NetworkLoad;
    long long unsigned NumCalls;
    std::vector<TransmissionBitrate> Bitrates;
};

#endif // MOSTUSED_H
