#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Generation.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h>

NSGA2_Generation::NSGA2_Generation() {

}

void NSGA2_Generation::evalCrowdingDistances() {

}

void NSGA2_Generation::eval() {
    for (auto &individual : people) {
        individual->eval();
    }
}
