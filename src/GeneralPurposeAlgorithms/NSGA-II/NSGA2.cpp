#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Generation.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h>
#include <GeneralClasses/RandomGenerator.h>

NSGA2::NSGA2() : generation(0) {

}

void NSGA2::natural_selection(NSGA2_Generation &gen, NSGA2_Generation &dest) {
    dest.people.clear();

    while (dest.people.size() < numIndiv)  {
        dest.people.push_back(gen.binaryTournament());
    }
}

void NSGA2::newGeneration(NSGA2_Generation &parent) {
    std::shared_ptr<NSGA2_Generation> gen_r(new NSGA2_Generation());
    std::shared_ptr<NSGA2_Generation> gen_q(new NSGA2_Generation());

    natural_selection(parent, *gen_r);

    while (!gen_r->people.empty()) {
        std::uniform_int_distribution<> dist(0, gen_r->people.size() - 1);

        auto indiv_a = gen_r->people[dist(random_generator)];
        auto indiv_b = gen_r->people[dist(random_generator)];
        gen_r->breed(*indiv_a, *indiv_b, *gen_q);
    }

    for (auto indiv : gen_q->people) {
        indiv->mutate();
    }

    evolution.push_back(gen_q);
}

void NSGA2::run_Generation() {
    if (evolution.empty()) {
        createInitialGeneration();
    }

    evolution.back()->eval();
    evolution.back()->evalParetoFront();
    evolution.back()->evalCrowdingDistances();

    newGeneration(*evolution.back());

    generation++;
}
