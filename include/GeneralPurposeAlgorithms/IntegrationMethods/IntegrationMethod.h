#ifndef INTEGRATIONMETHOD_H
#define INTEGRATIONMETHOD_H

#include <vector>

class IntegrationMethod
{
public:
    IntegrationMethod(std::vector<double>, double);
    std::vector<double> YPoints;
    double XRange;
    virtual double Calculate() = 0;
    void setValues(std::vector<double>, double);
};

#endif // INTEGRATIONMETHOD_H
