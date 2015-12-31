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

void Simulation_NSGA2_RegnPlacement::Individual::createIndividual() {
    Gene.clear();

    for (unsigned int gene = 0; gene < Sim.T->Nodes.size(); gene++) {
        Gene.push_back(createGene(gene));
    }
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
