#ifndef NSGA2_PARAMETER_CAPEX_H
#define NSGA2_PARAMETER_CAPEX_H

#include "Simulation_NSGA2_RegnPlac.h"

namespace Simulations
{
namespace NSGA2_Parameters
{
/**
 * @brief The NSGA2_Parameter_CapEx class is a parameter to the  MORP algorithm,
 * that implements the CapEx cost parameter.
 */
class NSGA2_Parameter_CapEx : public NSGA2_Parameter
{
    friend class Simulation_NSGA2_RegnPlac;

public:
    NSGA2_Parameter_CapEx(std::vector<int> gene, Simulation_NSGA2_RegnPlac &Sim);
    double evaluate();
    std::string get_ParamName()
    {
        return "CapEx";
    }

private:
    Simulation_NSGA2_RegnPlac &Sim;
};
}
}

#endif // NSGA2_PARAMETER_CAPEX_H
