#ifndef SIGNALQUALITYPREDICTION_VARIANTS_H
#define SIGNALQUALITYPREDICTION_VARIANTS_H

#include "SignalQualityPrediction.h"
#include <boost/bimap.hpp>

class SignalQualityPrediction_Variants : public SignalQualityPrediction
{
public:
#define SQPVARIANTS \
  X(mSCH, "Minimum Scheme") \
  X(MSCH, "Maximum Scheme")

#define X(a,b) a,
    enum SQP_Variants
    {
        SQPVARIANTS
    };
#undef X

    SignalQualityPrediction_Variants(std::shared_ptr<Topology> T,
                                     std::shared_ptr<RoutingWavelengthAssignment> RWA,
                                     double NetworkLoad,
                                     long long unsigned NumCalls,
                                     std::vector<TransmissionBitrate> Bitrates =
                                         TransmissionBitrate::DefaultBitrates);

    void load();

private:
    static SQP_Variants Variant;
    static bool chooseVariant;

    typedef boost::bimap<SQP_Variants, std::string> SQPVariantNameBimap;
    static SQPVariantNameBimap SQPVariantNames;

    void chooseSQPVariant();

    void evaluateLNMax();
};

#endif // SIGNALQUALITYPREDICTION_VARIANTS_H
