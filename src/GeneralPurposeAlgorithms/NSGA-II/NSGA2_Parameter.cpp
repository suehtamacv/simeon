#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Parameter.h>

using namespace NSGA_II;

NSGA2_Parameter::NSGA2_Parameter(std::vector<int> gene) :
    isEvaluated(false), value(-1), gene(gene)
{

}

bool NSGA2_Parameter::operator ==(const NSGA2_Parameter &other) const
{
    return value == other.value;
}

void NSGA2_Parameter::setValue(double val)
{
    isEvaluated = true;
    value = val;
}
