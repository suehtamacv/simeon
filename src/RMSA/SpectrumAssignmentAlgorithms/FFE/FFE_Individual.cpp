#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Individual.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Generation.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_GA.h"
#include "include/Calls/CallGenerator.h"
#include "include/RMSA/RoutingAlgorithms/RoutingAlgorithm.h"
#include "include/RMSA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FirstFitEvolutionary.h"
#include "include/Structure/Link.h"
#include "include/GeneralClasses/RandomGenerator.h"
#include "include/SimulationTypes/Simulation_FFE_Optimization.h"
#include "include/SimulationTypes/NetworkSimulation.h"
#include <algorithm>

using namespace RMSA::SA::FFE;
using namespace GeneticAlgorithm;

FFE_Individual::FFE_Individual(FFE_Generation *G) : GA_Individual(), G(G)
{
    createIndividual();
}

void FFE_Individual::createIndividual()
{
    for (auto &nS : SpectrumAssignmentAlgorithm::possibleRequiredSlots)
        {
        Gene[nS] = std::vector<int>(Link::NumSlots);
        std::iota(Gene[nS].begin(), Gene[nS].end(), 0);
        std::random_shuffle(Gene[nS].begin(), Gene[nS].end());
        }
}

int FFE_Individual::createGene(unsigned int g)
{
    std::uniform_int_distribution<unsigned int> dist(0, Link::NumSlots - 1);
    unsigned int newGene;

    do
        {
        newGene = dist(random_generator);
        }
    while (g == newGene);

    return newGene;
}

void FFE_Individual::eval()
{
    auto TCopy = std::make_shared<Topology>(*(G->GA->Sim.T));

    std::shared_ptr<ROUT::RoutingAlgorithm> R_Alg =
        ROUT::RoutingAlgorithm::create_RoutingAlgorithm(G->GA->Sim.Routing_Algorithm,
                G->GA->Sim.Routing_Cost, TCopy);
    auto FFE = std::make_shared<FirstFitEvolutionary>(TCopy);
    std::shared_ptr<RA::RegeneratorAssignmentAlgorithm> RA_Alg = nullptr;

    if (G->GA->Sim.Type == Simulations::SimulationType::TranslucentNetwork)
        {
        RA_Alg = RA::RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
                     G->GA->Sim.RegAssignment_Algorithm, TCopy);
        }

    //Initializes slots list
    FFE->setSlotsList(Gene);

    //Creates the Call Generator and the RMSA Object
    auto Generator = std::make_shared<CallGenerator>
                     (TCopy, G->GA->Sim.OptimizationLoad);
    auto RMSA = std::make_shared<RoutingWavelengthAssignment>
                (R_Alg, FFE, RA_Alg, ModulationScheme::DefaultSchemes, TCopy);

    parameter = Simulations::NetworkSimulation(Generator, RMSA, G->GA->Sim.NumCalls)
                .get_CallBlockingProbability();

    isEvaluated = true;
}

std::shared_ptr<GA_Individual> FFE_Individual::clone()
{
    std::shared_ptr<FFE_Individual> individual =
        std::make_shared<FFE_Individual>(G);
    individual->Gene = Gene;
    individual->parameter = parameter;
    individual->isEvaluated = isEvaluated;
    return individual;
}

GA_Individual& FFE_Individual::mutate()
{
    GA_Individual::mutate();

    for (auto &list : Gene)
        {
        std::uniform_int_distribution<int> dist(0, list.second.size() - 1);
        for (unsigned gene = 0; gene < GA::mutationPoints; ++gene)
            {
            int g = dist(random_generator);
            std::swap(list.second[g], list.second[createGene(g)]);
            isEvaluated = false;
            }
        }

    return *this;
}
