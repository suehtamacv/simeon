#ifndef INTEGRATIONMETHOD_H
#define INTEGRATIONMETHOD_H

#include <armadillo>

//! Contains miscelaneous numeric methods required by the simulator.
namespace NumericMethods
{
/**
 * @brief The IntegrationMethod class represents a numerical integration method.
 */
class IntegrationMethod
{
public:
    /**
     * @brief IntegrationMethod is a constructor for an IntegrationMethod.
     */
    IntegrationMethod();
    /**
     * @brief calculate is used to compute the IntegrationMethod.
     * @return the result of the calculations.
     */
    virtual double calculate(arma::mat const &YPoints, const double XRange) = 0;
};
}

#endif // INTEGRATIONMETHOD_H
