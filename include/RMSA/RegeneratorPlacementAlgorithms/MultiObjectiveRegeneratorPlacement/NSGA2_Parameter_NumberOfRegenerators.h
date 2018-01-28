#ifndef NSGA2_PARAMETER_NUMBEROFREGENERATORS_H
#define NSGA2_PARAMETER_NUMBEROFREGENERATORS_H

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
 * @brief The NSGA2_Parameter_NumberOfRegenerators class is a parameter to the
 * MORP algorithm, that implements the number of electronic regenerators parameter.
 */
class NSGA2_Parameter_NumberOfRegenerators : public NSGA_II::NSGA2_Parameter
{
public:
    NSGA2_Parameter_NumberOfRegenerators
    (std::vector<int> gene, Simulations::Simulation_NSGA2_RegnPlac &Sim);
    double evaluate();
    std::string get_ParamName()
    {
        return "Number of Regenerators";
    }
};
}
}
}

#endif // NSGA2_PARAMETER_NUMBEROFREGENERATORS_H
