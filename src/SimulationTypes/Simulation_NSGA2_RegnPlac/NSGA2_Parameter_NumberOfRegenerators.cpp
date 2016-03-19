#include "include/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_NumberOfRegenerators.h"

using namespace Simulations::NSGA2_Parameters;

NSGA2_Parameter_NumberOfRegenerators::NSGA2_Parameter_NumberOfRegenerators
(std::vector<int> gene, Simulation_NSGA2_RegnPlac &) :
    NSGA2_Parameter(gene)
{

}

double NSGA2_Parameter_NumberOfRegenerators::evaluate()
{
    if (!isEvaluated)
        {
        value = 0;
        for (auto &g : gene)
            {
            value += g;
            }
        isEvaluated = true;
        }

    return value;
}
