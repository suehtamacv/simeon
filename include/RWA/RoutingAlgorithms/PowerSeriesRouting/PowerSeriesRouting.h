#ifndef POWERSERIESROUTING_H
#define POWERSERIESROUTING_H

#include <RWA/RoutingAlgorithms/DijkstraRoutingAlgorithm.h>
#include <armadillo>
#include <vector>

namespace PSR
{
class Cost;
}

class PowerSeriesRouting : public DijkstraRoutingAlgorithm
{
public:
#define PSRVARIANTS \
    X(Variant_MatricialPSR, "Standard PSR", MatricialPowerSeriesRouting) \
    X(Variant_AWR, "Adaptative Weighing Routing", AdaptativeWeighingRouting)

#define X(a,b,c) a,
    enum Variants
    {
        PSRVARIANTS
    };
#undef X

    typedef boost::bimap<Variants, std::string> VariantNameBimap;
    static VariantNameBimap VariantNames;
    typedef boost::bimap<Variants, std::string> VariantNicknameBimap;
    static VariantNicknameBimap VariantNicknames;

    PowerSeriesRouting(std::shared_ptr<Topology> T,
                       Variants = Variant_MatricialPSR);
    PowerSeriesRouting(std::shared_ptr<Topology> T,
                       std::vector<std::shared_ptr<PSR::Cost>> Costs,
                       Variants = Variant_MatricialPSR);

    void load();
    void save(std::string);
    bool initCoefficients(std::vector<double> X);
    bool initCoefficients(std::string);

    std::vector<std::shared_ptr<PSR::Cost>> get_Costs();

    int get_NMin() const;
    int get_NMax() const;

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

    static arma::mat defaultcoefficients;
    static std::vector<std::shared_ptr<PSR::Cost>> defaultcosts;

    Variants PSRVariant;
};

#endif // POWERSERIESROUTING_H

