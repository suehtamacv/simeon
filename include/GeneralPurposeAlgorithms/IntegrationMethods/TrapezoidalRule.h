#ifndef TRAPEZOIDALRULE_H
#define TRAPEZOIDALRULE_H

#include <GeneralPurposeAlgorithms/IntegrationMethods/IntegrationMethod.h>

class TrapezoidalRule : public IntegrationMethod
{
public:
    TrapezoidalRule(std::vector<double>, double);
    double Calculate();
};

#endif // TRAPEZOIDALRULE_H
