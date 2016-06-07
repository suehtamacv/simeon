#ifndef SIMPSONSRULE_H
#define SIMPSONSRULE_H

#include <include/GeneralPurposeAlgorithms/IntegrationMethods/IntegrationMethod.h>

namespace NumericMethods
{
/**
 * @brief The SimpsonsRule class represents the Simpson's Rule numerical integration method.
 */
class SimpsonsRule : public IntegrationMethod
{
public:
    /**
     * @brief SimpsonsRule is a constructor for a SimpsonsRule object.
     */
    SimpsonsRule();
    /**
     * @brief calculate is used to compute the SimpsonsRule integration method.
     * @return the result of the calculations.
     */
    double calculate(const arma::mat &, const double &);
};
}

#endif // SIMPSONSRULE_H
