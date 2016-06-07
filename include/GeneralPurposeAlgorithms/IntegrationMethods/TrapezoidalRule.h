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
    TrapezoidalRule();
    /**
     * @brief calculate is used to compute the SimpsonsRule integration method.
     * @return the result of the calculations.
     */
    double calculate(const arma::mat &, const double&);
};
}

#endif // TRAPEZOIDALRULE_H
