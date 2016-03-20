#ifndef NSGA2_INDIVIDUAL_H
#define NSGA2_INDIVIDUAL_H

#include <memory>
#include <vector>

class NSGA2_Generation;
class NSGA2_Parameter;

/**
 * @brief The NSGA2_Individual class represents a single Individual to the NSGA2.
 */
class NSGA2_Individual
{
    friend class NSGA2;

public:
    /**
     * @brief NSGA2_Individual is the default constructor.
     */
    NSGA2_Individual();

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
    virtual std::shared_ptr<NSGA2_Individual> clone() = 0;

    /**
     * @brief operator == compairs two Individuals for equality.
     * @param other is the other Individual.
     * @return true iff the Individuals are equal.
     */
    bool operator==(const NSGA2_Individual &other) const;
    /**
     * @brief operator < compairs two Individuals for ordering.
     * @param other is the other Individual.
     * @return true (this is "less" than other) if the Pareto Front of this
     * Individual is inner than the other's, or if they're in the same Pareto
     * Front but this Individual has smaller Crowding Distance.
     */
    bool operator<(const NSGA2_Individual &other) const;

    /**
     * @brief eval evaluates all the Parameters of this Individual.
     */
    void eval();
    /**
     * @brief print prints details about this Individual.
     */
    void print();

    /**
     * @brief getParameterValue returns the value of the i-th Parameter.
     * @param i is the i-th Parameter.
     * @return the value of the i-th Parameter.
     */
    double getParameterValue(unsigned int i) const;
    /**
     * @brief getParameter returns a pointer to the i-th Parameter.
     * @param i is the i-th Parameter.
     * @return a pointer to the i-th Parameter.
     */
    std::shared_ptr<NSGA2_Parameter> getParameter(unsigned int i) const;

    /**
     * @brief crowdingDistance measures how close this Individual is from the
     * other Individuals in the same Pareto Front.
     */
    double crowdingDistance;
    /**
     * @brief paretoFront is the Pareto Front of this Individual.
     */
    int paretoFront;
    /**
     * @brief getNumParameters returns the number of Parameters of this individual.
     * @return the number of Parameters of this individual.
     */
    unsigned int getNumParameters() const;
    /**
     * @brief isDominated returns true iff this Individual is dominated by other,
     * that is, if this Individual is better than the other in at least one
     * Parameter, and not worse in the remaining Parameters.
     * @param other is the other Individual.
     * @return true if this Individual is dominated by other.
     */
    bool isDominatedBy(const std::shared_ptr<NSGA2_Individual> other) const;
    /**
     * @brief mutate mutates this Individual.
     * @return a reference to this Individual, mutated.
     */
    NSGA2_Individual &mutate();
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
protected:
    std::vector<std::shared_ptr<NSGA2_Parameter>> Parameters;
    /**
     * @brief Gene is the genes of this Individual.
     */
    std::vector<int> Gene;
};

#endif // NSGA2_INDIVIDUAL_H
