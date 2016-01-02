#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Generation.h>
#include <GeneralPurposeAlgorithms/NSGA-II/NSGA2_Individual.h>
#include <GeneralClasses/RandomGenerator.h>
#include <algorithm>

NSGA2::NSGA2() : generation(0) {

}

void NSGA2::natural_selection(NSGA2_Generation &gen, NSGA2_Generation &dest) {
    dest.people.clear();

    while (dest.people.size() < numIndiv)  {
        dest.people.push_back(gen.binaryTournament());
    }
}

std::shared_ptr<NSGA2_Generation> NSGA2::newGeneration(NSGA2_Generation &prnt) {
    std::shared_ptr<NSGA2_Generation> gen_r(new NSGA2_Generation());
    std::shared_ptr<NSGA2_Generation> gen_q(new NSGA2_Generation());

    natural_selection(prnt, *gen_r);

    while (!gen_r->people.empty()) {
        std::uniform_int_distribution<> dist(0, gen_r->people.size() - 1);

        auto indiv_a = gen_r->people[dist(random_generator)];
        auto indiv_b = gen_r->people[dist(random_generator)];
        gen_r->breed(*indiv_a, *indiv_b, *gen_q);
    }

    for (auto indiv : gen_q->people) {
        indiv->mutate();
    }

    return gen_q;
}

void NSGA2::run_Generation() {
    if (evolution.empty()) {
        createInitialGeneration();
    }

    evolution.back()->eval();

    auto currentgeneration = *evolution.back();

    currentgeneration.operator +=(newGeneration(currentgeneration));
    currentgeneration.eval();

    std::shared_ptr<NSGA2_Generation> newGen(new NSGA2_Generation());
    int paretoFront = 1;

    do {
        auto currentFront = currentgeneration.getParetoFront(paretoFront++);

        if (newGen->people.size() + currentFront.size() <= numIndiv) {
            for (auto indiv : currentFront) {
                newGen->operator +=(indiv);
            }
        } else {
            break;
        }
    } while (1);

    auto currentFront = currentgeneration.getParetoFront(paretoFront);

    class Comparisor {
      public:
        static bool comp(const std::shared_ptr<NSGA2_Individual> &a,
                         const std::shared_ptr<NSGA2_Individual> &b) {
            return *a < *b;
        }
    };

    std::sort(currentFront.rbegin(), currentFront.rend(), Comparisor::comp);

    for (auto indiv : currentFront) {
        newGen->operator +=(indiv);

        if (newGen->people.size() >= numIndiv) {
            break;
        }
    }

    evolution.push_back(newGen);

    generation++;
}
