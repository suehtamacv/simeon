#ifndef TRAPEZOIDALRULE_H
#define TRAPEZOIDALRULE_H

#include <GeneralPurposeAlgorithms/IntegrationMethods/IntegrationMethod.h>

namespace NumericMethods
{
/**
 * @brief The TrapezoidalRule class represents the Trapezoidal Rule numerical integration method.
 */
class TrapezoidalRule : public IntegrationMethod
{
public:
    /**
     * @brief TrapezoidalRule is a constructor for a TrapezoidalRule object.
     */
    TrapezoidalRule(arma::mat &, double);
    /**
     * @brief calculate is used to compute the SimpsonsRule integration method.
     * @return the result of the calculations.
     */
    double calculate();
};
}

#endif // TRAPEZOIDALRULE_H
