#ifndef SIMPSONSRULE_H
#define SIMPSONSRULE_H

#include <include/GeneralPurposeAlgorithms/IntegrationMethods/IntegrationMethod.h>

class SimpsonsRule : public IntegrationMethod
{
public:
    SimpsonsRule(arma::mat &, double);
    double calculate();
};

#endif // SIMPSONSRULE_H
