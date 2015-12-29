#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Parameter.h>

NSGA2_Individual::NSGA2_Individual(std::weak_ptr<NSGA2_Generation> generation) :
    isEvaluated(false),
    crowdingDistance(-1),
    paretoFront(-1),
    generation(generation) {

}

void NSGA2_Individual::eval() {
    for (auto &parameter : Parameters) {
        parameter->evaluate();
    }
}
