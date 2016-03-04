#ifndef SIMPSONSRULE_H
#define SIMPSONSRULE_H

#include <include/GeneralPurposeAlgorithms/IntegrationMethods/IntegrationMethod.h>

class SimpsonsRule : public IntegrationMethod
{
public:
    SimpsonsRule(std::vector<double>, double);
    double Calculate();
};

#endif // SIMPSONSRULE_H
