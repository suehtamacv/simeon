#ifndef SIGNALQUALITYPREDICTION_H
#define SIGNALQUALITYPREDICTION_H

#include "NX_RegeneratorPlacement.h"
#include <GeneralClasses/TransmissionBitrate.h>
#include <GeneralClasses/ModulationScheme.h>
#include <map>

class SignalQualityPrediction : public NX_RegeneratorPlacement
{
public:
    SignalQualityPrediction(std::shared_ptr<Topology> T,
                            std::shared_ptr<RoutingWavelengthAssignment> RWA,
                            double NetworkLoad,
                            long long unsigned NumCalls,
                            std::vector<TransmissionBitrate> Bitrates =
                                TransmissionBitrate::DefaultBitrates);
    void placeRegenerators(unsigned, unsigned);

protected:
    std::shared_ptr<RoutingWavelengthAssignment> RWA;
    double NetworkLoad;
    long long unsigned NumCalls;
    std::vector<TransmissionBitrate> Bitrates;

    std::map<std::pair<TransmissionBitrate, ModulationScheme>, unsigned> LNMax;

    void evaluateLNMax();
};

#endif // SIGNALQUALITYPREDICTION_H
