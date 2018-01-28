#include "include/RMSA/RegeneratorPlacementAlgorithms/MultiObjectiveRegeneratorPlacement/NSGA2_Parameter_NumberOfRegenerators.h"
#include "include/SimulationTypes/Simulation_NSGA2_RegnPlac.h"

using namespace RMSA::RP::MORP;

NSGA2_Parameter_NumberOfRegenerators::NSGA2_Parameter_NumberOfRegenerators
(std::vector<int> gene, Simulations::Simulation_NSGA2_RegnPlac &) :
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
