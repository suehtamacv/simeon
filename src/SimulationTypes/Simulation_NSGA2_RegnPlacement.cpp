#include <SimulationTypes/Simulation_NSGA2_RegnPlacement.h>
#include <GeneralClasses/RandomGenerator.h>
#include <SimulationTypes/NetworkSimulation.h>
#include <GeneralClasses/TransmissionBitrate.h>
#include <GeneralClasses/ModulationScheme.h>
#include <Structure/Link.h>
#include <RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>
#include <algorithm>
#include <cmath>

unsigned int Simulation_NSGA2_RegnPlacement::RegnMax;

Simulation_NSGA2_RegnPlacement::Simulation_NSGA2_RegnPlacement() {
    auto maxBitrate = std::max(TransmissionBitrate::DefaultBitrates.begin(),
                               TransmissionBitrate::DefaultBitrates.end());
    auto maxScheme = std::max(ModulationScheme::DefaultSchemes.begin(),
                              ModulationScheme::DefaultSchemes.end());
    int MaxNumSlots = maxScheme->get_NumSlots(*maxBitrate);
    RegnMax = std::floor(Link::NumSlots / MaxNumSlots) * std::ceil(
                  maxBitrate->get_Bitrate() / RegeneratorAssignmentAlgorithm::RegeneratorBitrate);
}

Simulation_NSGA2_RegnPlacement::Param_CapEx::Param_CapEx(std::vector<int> gene,
        Simulation_NSGA2_RegnPlacement &Sim) :
    NSGA2_Parameter(gene), Sim(Sim) {

}

double Simulation_NSGA2_RegnPlacement::Param_CapEx::evaluate() {
    Topology T(*Sim.T);

    for (unsigned int i = 0; i < gene.size(); i++) {
        T.Nodes[i]->set_NumRegenerators(gene[i]);
    }

    return T.get_CapEx();
}

Simulation_NSGA2_RegnPlacement::Param_OpEx::Param_OpEx(std::vector<int> gene,
        Simulation_NSGA2_RegnPlacement &Sim) :
    NSGA2_Parameter(gene), Sim(Sim) {

}

double Simulation_NSGA2_RegnPlacement::Param_OpEx::evaluate() {
    Topology T(*Sim.T);

    for (unsigned int i = 0; i < gene.size(); i++) {
        T.Nodes[i]->set_NumRegenerators(gene[i]);
    }

    return T.get_OpEx();
}

void Simulation_NSGA2_RegnPlacement::Individual::createIndividual() {
    std::vector<int> IndivGene;

    for (unsigned int gene = 0; gene < Sim.T->Nodes.size(); gene++) {
        IndivGene.push_back(createGene(gene));
    }

    setGene(IndivGene);
}

int Simulation_NSGA2_RegnPlacement::Individual::createGene(unsigned int) {
    std::uniform_real_distribution<double> isTranslucent(0, 1);

    if (isTranslucent(random_generator) < 0.5) {
        std::uniform_int_distribution<unsigned int>
        numReg(0, Simulation_NSGA2_RegnPlacement::RegnMax);

        return numReg(random_generator);
    } else {
        return 0;
    }
}

std::shared_ptr<NSGA2_Individual>
Simulation_NSGA2_RegnPlacement::Individual::clone() {

    std::shared_ptr<Individual> indiv(new Individual(Sim));
    indiv->setGene(Gene);
    return indiv;
}

void Simulation_NSGA2_RegnPlacement::Individual::setGene(
    std::vector<int> gene) {
    Gene = gene;
    Parameters.push_back(std::shared_ptr<NSGA2_Parameter>(
                             new Param_CapEx(Gene, Sim)));
    Parameters.push_back(std::shared_ptr<NSGA2_Parameter>(
                             new Param_OpEx(Gene, Sim)));
}

Simulation_NSGA2_RegnPlacement::Sim_NSGA2::Sim_NSGA2(
    Simulation_NSGA2_RegnPlacement &Sim) : Sim(Sim) {

}

void Simulation_NSGA2_RegnPlacement::Sim_NSGA2::createInitialGeneration() {
    std::shared_ptr<NSGA2_Generation> gen(new NSGA2_Generation());

    for (unsigned i = 0; i < NSGA2::numIndiv; i++) {
        std::shared_ptr<Individual> indiv(new Individual(Sim));
        indiv->createIndividual();

        *gen += indiv;
    }

    evolution.push_back(gen);
}
