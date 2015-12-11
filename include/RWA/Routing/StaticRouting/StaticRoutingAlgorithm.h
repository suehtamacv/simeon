#ifndef STATICROUTINGALGORITHM_H
#define STATICROUTINGALGORITHM_H

#include <RWA/Routing/DijkstraRoutingAlgorithm.h>
#include <Structure/Link.h>
#include <map>

class StaticRoutingAlgorithm : public DijkstraRoutingAlgorithm {
  public:
    StaticRoutingAlgorithm(std::shared_ptr<Topology> T);

    std::vector<std::weak_ptr<Link>> route(std::shared_ptr<Call> C);

    std::map<OrigDestPair, std::vector<std::weak_ptr<Link>>> Routes;
  private:
    void precalculate_Routes();
};

#endif // STATICROUTINGALGORITHM_H
