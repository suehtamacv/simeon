#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Generation.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h>
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

void NSGA2_Generation::evalCrowdingDistances() {
    if (!isEvaluated) {
        eval();
    }

    unsigned int numParameters = people.front()->getNumParameters();

    //Initialize crowding distances
    for (auto &individual : people) {
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

        for (auto indiv : people) {
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
