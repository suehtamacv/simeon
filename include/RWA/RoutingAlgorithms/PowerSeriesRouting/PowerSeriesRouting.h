#ifndef POWERSERIESROUTING_H
#define POWERSERIESROUTING_H

#include <RWA/RoutingAlgorithms/DijkstraRoutingAlgorithm.h>
#include <GeneralPurposeAlgorithms/PSO/PSO_Particle.h>
#include <vector>
#include "Costs.h"

class PowerSeriesRouting : public DijkstraRoutingAlgorithm {
  public:
    PowerSeriesRouting(std::shared_ptr<Topology> T);
    PowerSeriesRouting(std::shared_ptr<Topology> T,
                       std::vector<std::shared_ptr<PSR::Cost>> Costs);

    void load();
    bool initCoefficients(PSO::PSO_Particle<double> &particle);
    bool initCoefficients(std::string);

    double get_Cost(std::weak_ptr<Link> link,
                         std::shared_ptr<Call> C);
    std::vector<std::shared_ptr<PSR::Cost>> get_Costs();

    int get_NMin() const;
    int get_NMax() const;

  private:
    std::vector<std::shared_ptr<PSR::Cost>> Costs;
    arma::mat coefficients;
    int NMin, NMax;

    bool firstTimeRun;
    static bool hasLoaded;

    static arma::mat defaultcoefficients;
    static std::vector<std::shared_ptr<PSR::Cost>> defaultcosts;
};

#endif // POWERSERIESROUTING_H

