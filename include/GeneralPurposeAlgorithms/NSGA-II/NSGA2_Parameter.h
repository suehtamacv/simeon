#ifndef NSGA2_PARAMETER_H
#define NSGA2_PARAMETER_H

#include <vector>
#include <string>

/**
 * @brief The NSGA2_Parameter class represents a Parameter to a NSGA2_Individual.
 */
class NSGA2_Parameter
{
    friend class NSGA2;

public:
    /**
     * @brief NSGA2_Parameter is the default constructor.
     * @param gene is the Individual's genes.
     */
    NSGA2_Parameter(std::vector<int> gene);
    /**
     * @brief evaluate evaluates this Parameter.
     * @return the result of the evaluation.
     */
    virtual double evaluate() = 0;
    /**
     * @brief get_ParamName returns the name of this Parameter.
     * @return the name of this Parameter.
     */
    virtual std::string get_ParamName() = 0;
    /**
     * @brief operator == compairs two Parameters for equality.
     * @param other is the other Parameter.
     * @return true iff the value is equal.
     */
    bool operator == (const NSGA2_Parameter &other) const;

protected:
    bool isEvaluated;
    double value;
    std::vector<int> gene;
};

#endif // NSGA2_PARAMETER_H
