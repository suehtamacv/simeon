#ifndef POWERSERIESROUTING_H
#define POWERSERIESROUTING_H

#include <RMSA/RoutingAlgorithms/RoutingCost.h>
#include <armadillo>
#include <vector>

namespace RMSA
{
namespace ROUT
{

//! Calculations and costs to the Power Series Routing (PSR) routing algorithm.
namespace PSR
{
class Cost;
}

namespace PSR
{
/**
 * @brief The PowerSeriesRouting class represents the Power Series Routing algorithm.
 * Its link cost is a truncated power series of carefully chosen costs.
 */
class PowerSeriesRouting : public RoutingCost
{
public:
#define PSRVARIANTS \
    X(Variant_AWR, "Adaptative Weighing Routing", "awr", AdaptativeWeighingRouting) \
    X(Variant_LocalPSR, "Local PSR", "localPSR", LocalPowerSeriesRouting) \
    X(Variant_MatricialPSR, "Matricial PSR (Standard)", "matricialPSR", MatricialPowerSeriesRouting) \
    X(Variant_TensorialPSR, "Tensorial PSR", "tensorialPSR", TensorialPowerSeriesRouting)

#define X(a,b,c,d) a,
    enum Variants
    {
        PSRVARIANTS
    };
#undef X

    typedef boost::bimap<Variants, std::string> VariantNameBimap;
    static VariantNameBimap VariantNames;
    typedef boost::bimap<Variants, std::string> VariantNicknameBimap;
    static VariantNicknameBimap VariantNicknames;

    PowerSeriesRouting(std::shared_ptr<Topology> T, RoutingCosts RCost);
    PowerSeriesRouting(std::shared_ptr<Topology> T,
                       std::vector<std::shared_ptr<PSR::Cost>> Costs,
                       RoutingCosts RCost);

    void load();
    void save(std::string);

    bool initCoefficients(std::vector<double> X);
    bool initCoefficients(std::string);

    std::vector<std::shared_ptr<PSR::Cost>> get_Costs();

    int get_NMin() const;
    int get_NMax() const;
    int get_N() const;

    static std::shared_ptr<PowerSeriesRouting>
    createPSR(std::shared_ptr<Topology> T,
              std::vector<std::shared_ptr<PSR::Cost>> Costs,
              Variants Variant);

protected:
    std::vector<std::shared_ptr<PSR::Cost>> Costs;
    arma::mat coefficients;
    int NMin, NMax;

    bool firstTimeRun;
    static bool hasLoaded;

    Variants Variant;

    static arma::mat defaultcoefficients;
    static std::vector<std::shared_ptr<PSR::Cost>> defaultcosts;
};
}
}
}

#endif // POWERSERIESROUTING_H

