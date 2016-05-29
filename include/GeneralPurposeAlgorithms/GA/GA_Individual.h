#ifndef GA_INDIVIDUAL_H
#define GA_INDIVIDUAL_H

#include "GA.h"

namespace GeneticAlgorithm
{
class GA_Generation;

class GA_Individual
{
    friend class GA;
public:
    GA_Individual();

    /**
     * @brief createIndividual is used to create the Individual Genes. Must be
     * implemented by the user. It is called the first time this Individual is
     * being evaluated, if the Genes are not set by other means.
     */
    virtual void createIndividual() = 0;
    /**
     * @brief createGene returns the integer that represents the g-th Gene. It is
     * required by the Mutation function, and createIndividual() probably should
     * make use of this function.
     * @param g is the g-th Gene.
     * @return the g-th Gene.
     */
    virtual int createGene(unsigned int g) = 0;
    /**
     * @brief clone returns a clone of this Individual.
     * @return a clone of this Individual.
     */
    virtual std::shared_ptr<GA_Individual> clone() = 0;

    /**
     * @brief operator == compairs two Individuals for equality.
     * @param other is the other Individual.
     * @return true iff the Individuals are equal.
     */
    bool operator==(const GA_Individual &other) const;
    /**
     * @brief operator < compairs two Individuals for ordering.
     * @param other is the other Individual.
     * @return true (this is "less" than other) if the other Individual has a
     * smaller parameter.
     */
    bool operator<(const GA_Individual &other) const;

    /**
     * @brief eval evaluates all the Parameters of this Individual.
     */
    virtual void eval() = 0;
    /**
     * @brief print prints details about this Individual.
     */
    std::string print(bool pretty = true);

    /**
     * @brief mutate mutates this Individual.
     * @return a reference to this Individual, mutated.
     */
    GA_Individual &mutate();
    /**
     * @brief setGene sets the genes of this individual.
     * @param newGene are the new genes.
     */
    void setGene(std::vector<int> newGene);
    /**
     * @brief getGenes returns the genes of this individual.
     * @return the genes of this individual.
     */
    std::vector<int> getGenes() const;
    /**
     * @brief isEvaluated is true, if this Individual's Parameters have already
     * been evaluated.
     */
    bool isEvaluated;

    double getParameter() const
    {
        return parameter;
    }

protected:
    double parameter;
    std::vector<int> Gene;
};
}

#endif // GA_INDIVIDUAL_H
