#ifndef SHORTESTCOSTREGENERATORASSIGNMENT_H
#define SHORTESTCOSTREGENERATORASSIGNMENT_H

#include "RegeneratorAssignmentAlgorithm.h"

namespace RMSA
{
namespace RA
{
class ShortestCostRegeneratorAssignment : public RegeneratorAssignmentAlgorithm
{
public:
    ShortestCostRegeneratorAssignment(std::shared_ptr<Topology> T,
                                      std::set<ModulationScheme> Schemes);
    std::vector<TransparentSegment> assignRegenerators(
        std::shared_ptr<Call>, std::vector<std::weak_ptr<Link>>);
    void load();
    void save(std::string);

private:
    double get_Cost(const TransparentSegment &segment,
                    std::vector<std::weak_ptr<Node>>,
                    std::shared_ptr<Call> C);

    static bool hasLoaded;
    static double dcLevel;
};
}
}

#endif // SHORTESTCOSTREGENERATORASSIGNMENT_H
