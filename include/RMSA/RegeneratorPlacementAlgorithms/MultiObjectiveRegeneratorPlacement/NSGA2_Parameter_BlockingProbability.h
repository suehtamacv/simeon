#ifndef NSGA2_PARAMETER_BLOCKINGPROBABILITY_H
#define NSGA2_PARAMETER_BLOCKINGPROBABILITY_H

#include "include/GeneralPurposeAlgorithms/NSGA-2.h"

namespace Simulations
{
class Simulation_NSGA2_RegnPlac;
}

namespace RMSA
{
namespace RP
{
namespace MORP
{
/**
 * @brief The NSGA2_Parameter_BlockingProbability class is a parameter to the
 * MORP algorithm, that implements the Call Request Blocking Probability parameter.
 */
class NSGA2_Parameter_BlockingProbability : public NSGA_II::NSGA2_Parameter
{
public:
    NSGA2_Parameter_BlockingProbability
    (std::vector<int> gene, Simulations::Simulation_NSGA2_RegnPlac &Sim);
    double evaluate();
    std::string get_ParamName()
    {
        return "Blocking Probability";
    }

private:
    Simulations::Simulation_NSGA2_RegnPlac &Sim;
};
}
}
}

#endif // NSGA2_PARAMETER_BLOCKINGPROBABILITY_H
