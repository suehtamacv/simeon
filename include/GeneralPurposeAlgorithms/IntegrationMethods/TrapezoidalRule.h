#ifndef TRAPEZOIDALRULE_H
#define TRAPEZOIDALRULE_H

#include <GeneralPurposeAlgorithms/IntegrationMethods/IntegrationMethod.h>

class TrapezoidalRule : public IntegrationMethod
{
public:
    TrapezoidalRule(arma::mat &, double);
    double calculate();
};

#endif // TRAPEZOIDALRULE_H
