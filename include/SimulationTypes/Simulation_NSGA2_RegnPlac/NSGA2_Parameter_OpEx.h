#ifndef NSGA2_PARAMETER_OPEX_H
#define NSGA2_PARAMETER_OPEX_H

#include "Simulation_NSGA2_RegnPlac.h"

namespace Simulations
{
namespace NSGA2_Parameters
{
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
