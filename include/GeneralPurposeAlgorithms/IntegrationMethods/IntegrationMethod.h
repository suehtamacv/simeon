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
     * @param YPoints are the points being integrated.
     * @param XRange is the length of the interval being integrated on.
     * @return the result of the calculations.
     */
    virtual double calculate(arma::mat const &YPoints, const double &XRange) = 0;
};
}

#endif // INTEGRATIONMETHOD_H
