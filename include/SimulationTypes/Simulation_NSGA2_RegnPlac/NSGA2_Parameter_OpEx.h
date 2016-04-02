#ifndef NSGA2_PARAMETER_OPEX_H
#define NSGA2_PARAMETER_OPEX_H

#include "Simulation_NSGA2_RegnPlac.h"

namespace Simulations
{
//! Parameters that can be used by the NSGA2 Regenerator Placement algorithm.
namespace NSGA2_Parameters
{
/**
 * @brief The NSGA2_Parameter_OpEx class is a parameter to the MORP algorithm,
 * that implements the OpEx cost parameter.
 */
class NSGA2_Parameter_OpEx : public NSGA2_Parameter
{
    friend class Simulation_NSGA2_RegnPlac;

public:
    NSGA2_Parameter_OpEx(std::vector<int> gene, Simulation_NSGA2_RegnPlac &Sim);
    double evaluate();
    std::string get_ParamName()
    {
        return "OpEx";
    }

private:
    Simulation_NSGA2_RegnPlac &Sim;
};
}
}


#endif // NSGA2_PARAMETER_OPEX_H
