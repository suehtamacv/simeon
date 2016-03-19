#ifndef NSGA2_PARAMETER_BLOCKINGPROBABILITY_H
#define NSGA2_PARAMETER_BLOCKINGPROBABILITY_H

#include "Simulation_NSGA2_RegnPlac.h"

namespace Simulations
{
namespace NSGA2_Parameters
{
class NSGA2_Parameter_BlockingProbability : public NSGA2_Parameter
{
    friend class Simulation_NSGA2_RegnPlac;

public:
    NSGA2_Parameter_BlockingProbability
    (std::vector<int> gene, Simulation_NSGA2_RegnPlac &Sim);
    double evaluate();
    std::string get_ParamName()
    {
        return "Blocking Probability";
    }

private:
    Simulation_NSGA2_RegnPlac &Sim;
};
}
}

#endif // NSGA2_PARAMETER_BLOCKINGPROBABILITY_H
