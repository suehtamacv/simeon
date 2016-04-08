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
    IntegrationMethod(arma::mat&, double);
    /**
     * @brief YPoints is a vector with the given function image values.
     */
    arma::mat YPoints;
    /**
     * @brief XRange is the domain to be integrated.
     */
    double XRange;
    /**
     * @brief calculate is used to compute the IntegrationMethod.
     * @return the result of the calculations.
     */
    virtual double calculate() = 0;
    /**
     * @brief setValues sets this IntegrationMethod YPoints and XRange values.
     */
    void setValues(arma::mat&, double);
};
}

#endif // INTEGRATIONMETHOD_H
