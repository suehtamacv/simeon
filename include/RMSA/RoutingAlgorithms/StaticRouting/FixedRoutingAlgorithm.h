#ifndef STATICROUTINGALGORITHM_H
#define STATICROUTINGALGORITHM_H

#include <RMSA/RoutingAlgorithms/DijkstraRoutingAlgorithm.h>
#include <map>

class Link;

namespace RMSA
{
namespace ROUT
{
/**
 * @brief The FixedRoutingAlgorithm class represents the Dijkstra-based routing
 * algorithms whose route between a certain pair of nodes does not change as the
 * simulation progresses.
 */
class FixedRoutingAlgorithm : public DijkstraRoutingAlgorithm
{
public:
    FixedRoutingAlgorithm(std::shared_ptr<Topology> T, RoutingAlgorithms RoutAlg);

    std::vector<std::weak_ptr<Link>> route(std::shared_ptr<Call> C);

    std::map<std::pair<int, int>, std::vector<std::weak_ptr<Link>>> Routes;
private:
    void precalculate_Routes();
};
}
}

#endif // STATICROUTINGALGORITHM_H
