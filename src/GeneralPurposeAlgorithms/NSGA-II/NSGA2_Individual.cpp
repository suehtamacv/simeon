#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Parameter.h>
#include <GeneralClasses/RandomGenerator.h>
#include <boost/assert.hpp>

NSGA2_Individual::NSGA2_Individual(std::weak_ptr<NSGA2_Generation> generation) :
    crowdingDistance(-1),
    paretoFront(-1),
    isEvaluated(false),
    isCreated(false),
    generation(generation) {

}

bool NSGA2_Individual::operator ==(const NSGA2_Individual &other) const {
    return (Gene == other.Gene);
}

void NSGA2_Individual::eval() {
    if (!isCreated) {
        createIndividual();
    }

    for (auto &parameter : Parameters) {
        parameter->evaluate();
    }
}

std::shared_ptr<NSGA2_Parameter> NSGA2_Individual::getParameter(
    unsigned int i) const {
    BOOST_ASSERT_MSG(i < Parameters.size(), "Invalid parameter requested");
    return Parameters[i];
}

double NSGA2_Individual::getParameterValue(unsigned int i) const {
    BOOST_ASSERT_MSG(i < Parameters.size(), "Invalid parameter requested");

    return Parameters[i]->evaluate();
}

unsigned int NSGA2_Individual::getNumParameters() const {
    return Parameters.size();
}

bool NSGA2_Individual::isDominated(const NSGA2_Individual &other) const {
    for (unsigned int i = 0; i < Parameters.size(); i++) {
        if (Parameters[i] < other.Parameters[i]) {
            bool Dominates = true;

            for (unsigned j = 0; j < Parameters.size(); j++) {
                Dominates &= Parameters[j] <= other.getParameter(j);
            }

            if (Dominates) {
                return true;
            }
        }
    }

    return false;
}

NSGA2_Individual &NSGA2_Individual::mutate() {
    crowdingDistance = paretoFront = -1;
    std::uniform_real_distribution<double> dist(0, 1);

    if (dist(random_generator) < NSGA2::mutationProb) { //mutates
        for (unsigned int i = 0; i < Gene.size(); i++) {
            Gene[i] = createGene();
        }
    }

    return *this;
}
