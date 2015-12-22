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
    void initCoefficients(PSO::PSO_Particle<double> particle);
    double get_Cost(std::weak_ptr<Link> link,
                         std::shared_ptr<Call> C);
    std::vector<std::shared_ptr<PSR::Cost>> get_Costs();

  private:
    std::vector<std::shared_ptr<PSR::Cost>> Costs;
    arma::mat coefficients;
    int NMin, NMax;

    bool firstTimeRun;
    bool hasLoaded;
};

#endif // POWERSERIESROUTING_H

