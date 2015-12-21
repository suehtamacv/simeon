#ifndef POWERSERIESROUTING_H
#define POWERSERIESROUTING_H

#include <RWA/RoutingAlgorithms/DijkstraRoutingAlgorithm.h>
#include <GeneralPurposeAlgorithms/PSO/PSO_Particle.h>
#include <vector>
#include "Costs.h"

class PowerSeriesRouting : public DijkstraRoutingAlgorithm {
  public:
    PowerSeriesRouting(std::shared_ptr<Topology> T);

    void load();
    long double get_Cost(std::weak_ptr<Link> link,
    					 std::shared_ptr<Call> C);

  private:
    std::vector<std::shared_ptr<PSR::Cost>> Costs;
    arma::mat coefficients;
};

#endif // POWERSERIESROUTING_H

