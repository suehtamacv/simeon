#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Generation.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2.h>
#include <GeneralClasses/RandomGenerator.h>
#include <algorithm>
#include <limits>
#include <set>

NSGA2_Generation::NSGA2_Generation() : isEvaluated(false) {

}

void NSGA2_Generation::eval() {
    for (auto &individual : people) {
        individual->eval();
    }

    isEvaluated = true;
}

void NSGA2_Generation::evalCrowdingDistances(int ParetoFront) {
    if (!isEvaluated) {
        eval();
    }

    auto front = getParetoFront(ParetoFront);
    unsigned int numParameters = people.front()->getNumParameters();

    //Initialize crowding distances
    for (auto &individual : front) {
        individual->crowdingDistance = 0;
    }

    for (unsigned int par = 0; par < numParameters; par++) {
        struct Param {
            Param(std::shared_ptr<NSGA2_Individual> individual, double value) :
                individual(individual), value(value) {}
            std::shared_ptr<NSGA2_Individual> individual;
            double value;
            bool operator < (const Param &other) const {
                return value < other.value;
            }
        };

        std::vector<Param> IndivList;

        for (auto indiv : front) {
            IndivList.push_back(Param(indiv, indiv->getParameterValue(par)));
        }

        std::sort(IndivList.begin(), IndivList.end());

        double minValue = IndivList.front().value;
        double maxValue = IndivList.back().value;

        //Extreme values have infinite crowding distance
        IndivList.front().individual->crowdingDistance =
            std::numeric_limits<double>::max();
        IndivList.back().individual->crowdingDistance =
            std::numeric_limits<double>::max();

        for (auto parameter = IndivList.begin() + 1;
                parameter != IndivList.end() - 1;
                ++parameter) {
            if (parameter->individual->crowdingDistance ==
                    std::numeric_limits<double>::max()) {
                continue;
            }

            parameter->individual->crowdingDistance +=
                ((parameter + 1)->value - (parameter - 1)->value) / (maxValue - minValue);
        }
    }
}

void NSGA2_Generation::evalParetoFront() {
    int numNotInParetoFront = 0;
    int currentParetoFront = 1;

    do {
        numNotInParetoFront = 0;

        for (auto &indiv : people) {
            if (indiv->paretoFront != -1) {
                continue;
            }

            bool isDominated = false;

            for (auto &other : people) {
                if (other->paretoFront != -1) {
                    continue;
                }

                isDominated |= indiv->isDominated(*other);

                if (isDominated) {
                    break;
                }
            }

            if (!isDominated) {
                indiv->paretoFront = currentParetoFront;
            }

            numNotInParetoFront++;
        }

        currentParetoFront++;
    } while (numNotInParetoFront != 0);
}

NSGA2_Generation &NSGA2_Generation::operator +=
(std::shared_ptr<NSGA2_Individual> &other) {
    isEvaluated = false;

    other->paretoFront = other->crowdingDistance = -1;
    people.push_back(other);

    return *this;
}

NSGA2_Generation &NSGA2_Generation::operator +=(NSGA2_Generation &other) {
    for (auto individual : other.people) {
        this->operator +=(individual);
    }

    return *this;
}

std::vector<std::shared_ptr<NSGA2_Individual>>
NSGA2_Generation::getParetoFront(int i) {
    if (!isEvaluated) {
        eval();
    }

    std::vector<std::shared_ptr<NSGA2_Individual>> ParetoFront;

    for (auto indiv : people) {
        if (indiv->paretoFront == i) {
            ParetoFront.push_back(indiv);
        }
    }

    return ParetoFront;
}

void NSGA2_Generation::breed(
    NSGA2_Individual &a, NSGA2_Individual &b, NSGA2_Generation &dest) {
    auto iterator_a = people.begin();
    auto iterator_b = people.begin();

    int found = 0;

    //finds iterators to the two individuals
    for (auto indiv = people.begin(); indiv != people.end(); ++indiv) {
        if (**indiv == a) {
            iterator_a = indiv;
            found++;
        }

        if (**indiv == b) {
            iterator_b = indiv;
            found++;
        }

        if (found == 2) {
            break;
        }
    }

    if (iterator_a == iterator_b) {
        return;
    }

    if (found == 2) {
        std::uniform_real_distribution<double> dist(0, 1);
        std::vector<int> GeneA = a.Gene, GeneB = b.Gene;

        if (dist(random_generator) < NSGA2::breedingProb) { //breeds
            for (unsigned int i = 0; i < GeneA.size(); ++i) {
                if (dist(random_generator) < 0.5) {
                    std::swap(GeneA[i], GeneB[i]); //swaps genes of the individuals
                }
            }
        }

        auto newIndivA = a.clone(), newIndivB = b.clone();
        newIndivA->Gene = GeneA;
        newIndivB->Gene = GeneB;
        dest += newIndivA;
        dest += newIndivB;

        people.erase(iterator_a);
        people.erase(iterator_b);
    }
}

std::shared_ptr<NSGA2_Individual> NSGA2_Generation::binaryTournament() {
    std::uniform_int_distribution<> dist(0, people.size());

    //selects random Individual
    auto individual = people.begin() + dist(random_generator);

    //selects binaryTournamentParameter other individuals to "duel" with
    //individual, in terms of Pareto Front.
    for (unsigned selec = 0; selec < NSGA2::binaryTournamentParameter; selec++) {
        auto adversary = people.begin() + dist(random_generator);

        if ((*adversary)->paretoFront < (*individual)->paretoFront) {
            individual = adversary;
        }
    }

    return *individual;
}
