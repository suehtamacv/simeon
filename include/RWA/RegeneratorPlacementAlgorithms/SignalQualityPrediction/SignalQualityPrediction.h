#ifndef SIGNALQUALITYPREDICTION_H
#define SIGNALQUALITYPREDICTION_H

#include "../NX_RegeneratorPlacement.h"
#include <GeneralClasses/TransmissionBitrate.h>
#include <GeneralClasses/ModulationScheme.h>
#include <map>

class SignalQualityPrediction : public NX_RegeneratorPlacement
{
public:
#define SQPTypes \
    X(HopsNumber, "Hops Number") \
    X(Distance, "Distance")

#define X(a,b) a,
    enum SQP_Type
    {
        SQPTypes
    };
#undef X

    SignalQualityPrediction(std::shared_ptr<Topology> T,
                            std::shared_ptr<RoutingWavelengthAssignment> RWA,
                            double NetworkLoad,
                            long long unsigned NumCalls,
                            std::vector<TransmissionBitrate> Bitrates =
                                TransmissionBitrate::DefaultBitrates);

    void placeRegenerators(unsigned N = NX_N, unsigned X = NX_X);
    void load();
    void chooseSQPType();

    double get_LNMax(TransmissionBitrate, ModulationScheme);

    static SQP_Type Type;

protected:
    typedef boost::bimap<SQP_Type, std::string> SQPTypeNameBimap;
    static SQPTypeNameBimap SQPTypeNames;

    static bool chosenType;

    std::shared_ptr<RoutingWavelengthAssignment> RWA;
    double NetworkLoad;
    long long unsigned NumCalls;
    std::vector<TransmissionBitrate> Bitrates;

    std::map<std::pair<TransmissionBitrate, ModulationScheme>, unsigned long> LNMax;

    void evaluateLNMax();
};

#endif // SIGNALQUALITYPREDICTION_H
