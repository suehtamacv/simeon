#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Parameter.h>

NSGA2_Parameter::NSGA2_Parameter(std::vector<int> gene) :
    isEvaluated(false), value(-1), gene(gene)
{

}

bool NSGA2_Parameter::operator ==(const NSGA2_Parameter &other) const
{
    return value == other.value;
}
