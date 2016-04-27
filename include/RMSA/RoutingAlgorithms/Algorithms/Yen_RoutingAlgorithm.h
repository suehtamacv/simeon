#ifndef YEN_ROUTINGALGORITHM_H
#define YEN_ROUTINGALGORITHM_H

#include "../RoutingAlgorithm.h"

namespace RMSA
{
namespace ROUT
{
class Yen_RoutingAlgorithm : public RoutingAlgorithm
{
public:
    Yen_RoutingAlgorithm(std::shared_ptr<Topology> T);
    std::vector<std::vector<std::weak_ptr<Link>>> route(std::shared_ptr<Call> C);
};
}
}

#endif // YEN_ROUTINGALGORITHM_H
