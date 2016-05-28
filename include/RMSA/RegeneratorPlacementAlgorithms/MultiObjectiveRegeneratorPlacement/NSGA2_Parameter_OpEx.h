#ifndef NSGA2_PARAMETER_OPEX_H
#define NSGA2_PARAMETER_OPEX_H

#include "include/GeneralPurposeAlgorithms/NSGA-2.h"

namespace Simulations
{
class Simulation_NSGA2_RegnPlac;
}

namespace RMSA
{
namespace RP
{
//! Parameters that can be used by the MultiObjective Regenerator Placement algorithm.
namespace MORP
{
/**
 * @brief The NSGA2_Parameter_OpEx class is a parameter to the MORP algorithm,
 * that implements the OpEx cost parameter.
 */
class NSGA2_Parameter_OpEx : public NSGA_II::NSGA2_Parameter
{
    friend class Simulations::Simulation_NSGA2_RegnPlac;

public:
    NSGA2_Parameter_OpEx(std::vector<int> gene,
                         Simulations::Simulation_NSGA2_RegnPlac &Sim);
    double evaluate();
    std::string get_ParamName()
    {
        return "OpEx";
    }

private:
    Simulations::Simulation_NSGA2_RegnPlac &Sim;
};
}
}
}

#endif // NSGA2_PARAMETER_OPEX_H
