#ifndef INTEGRATIONMETHOD_H
#define INTEGRATIONMETHOD_H

#include <armadillo>

class IntegrationMethod
{
public:
    IntegrationMethod(arma::mat&, double);
    arma::mat YPoints;
    double XRange;
    virtual double Calculate() = 0;
    void setValues(arma::mat&, double);
};

#endif // INTEGRATIONMETHOD_H
