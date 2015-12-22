#include <SimulationTypes/Simulation_PSROptimization.h>
#include "Calls.h"
#include <GeneralPurposeAlgorithms/PSO.h>
#include <RWA.h>
#include <SimulationTypes/NetworkSimulation.h>
#include <Structure/Link.h>

double Simulation_PSROptimization::NumCalls;
double Simulation_PSROptimization::OptimizationLoad;
std::shared_ptr<Topology> Simulation_PSROptimization::Fitness::T;
std::shared_ptr<PowerSeriesRouting> Simulation_PSROptimization::MasterPSR;
WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms
Simulation_PSROptimization::WavAssign_Algorithm;
RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
Simulation_PSROptimization::RegPlacement_Algorithm;
RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
Simulation_PSROptimization::RegAssignment_Algorithm;

Simulation_PSROptimization::Simulation_PSROptimization() {
    hasLoaded = hasRun = false;
}

void Simulation_PSROptimization::help() {
    std::cout << "\t\tPSR OPTIMIZATION SIMULATION" << std::endl << std::endl <<
              "\tThis simulation runs the Particle Swarm Optimization algorithm"
              " to find a set of coefficients that minimize the call blocking"
              " probability of the network. Attention: this usually takes"
              " some time." << std::endl;
}

void Simulation_PSROptimization::load() {
    //Generic readings.
    SimulationType::load();

    std::cout << std::endl << "-> Choose a network type." << std::endl;

    do {
        for (auto nettype : NetworkTypes.left) {
            std::cout << "(" << nettype.first << ")\t" << nettype.second << std::endl;
        }

        int Net_Type;
        std::cin >> Net_Type;

        if (std::cin.fail() || NetworkTypes.left.count((NetworkType) Net_Type) == 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Network Type." << std::endl;
            std::cout << std::endl << "-> Choose a network type." << std::endl;
        } else {
            Type = (NetworkType) Net_Type;
            break;
        }
    } while (1);

    Node::load();

    Link::load();

    //RWA Algorithms
    {
        //Routing Algorithm
        MasterPSR = std::static_pointer_cast<PowerSeriesRouting>
                    (RoutingAlgorithm::create_RoutingAlgorithm(RoutingAlgorithm::PSR, T));

        //Wavelength Assignment Algorithm
        WavAssign_Algorithm =
            WavelengthAssignmentAlgorithm::define_WavelengthAssignmentAlgorithm();

        if (Type == TranslucentNetwork) {
            //Regenerator Placement Algorithm
            RegPlacement_Algorithm =
                RegeneratorPlacementAlgorithm::define_RegeneratorPlacementAlgorithm();

            //Regenerator Assignment Algorithm
            RegAssignment_Algorithm =
                RegeneratorAssignmentAlgorithm::define_RegeneratorAssignmentAlgorithm();
        }
    }

    std::cout << std::endl << "-> Define the number of calls." << std::endl;

    do {
        std::cin >> NumCalls;

        if (std::cin.fail() || NumCalls < 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of calls." << std::endl;
            std::cout << std::endl << "-> Define the number of calls." << std::endl;
        } else {
            break;
        }
    } while (1);

    std::cout << std::endl << "-> Define the optimization network load." <<
              std::endl;

    do {
        std::cin >> OptimizationLoad;

        if (std::cin.fail() || OptimizationLoad < 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the optimization network load." <<
                      std::endl;
        } else {
            break;
        }
    } while (1);

    hasLoaded = true;
}

void Simulation_PSROptimization::create_Simulation() {

}

void Simulation_PSROptimization::save(std::ofstream) {

}

void Simulation_PSROptimization::load_file(std::ifstream) {

}

void Simulation_PSROptimization::print() {
    if (!hasLoaded) {
        load();
    }

    if (!hasRun) {
        Fitness::T = T;
        int N = std::pow(MasterPSR->get_Costs().front()->get_N(),
                         MasterPSR->get_Costs().size());

        PSO::ParticleSwarmOptimization<double, Fitness, Compare>
        PSO_Optim(P, G, N, XMin, XMax, VMin, VMax);

        std::cout << std::endl << "* * RESULTS * *" << std::endl;

        for (unsigned i = 1; i <= G; i++) {
            PSO_Optim.run_generation();
            std::cout << "GENERATION\tCALL BLOCKING PROBABILITY" << std::endl;
            std::cout << i << "\t\t" << PSO_Optim.BestParticle->bestFit << std::endl;
        }
    }
}

void Simulation_PSROptimization::run() {
    if (!hasLoaded) {
        load();
    }

    Fitness::T = T;
    int N = std::pow(MasterPSR->get_Costs().front()->get_N(),
                     MasterPSR->get_Costs().size());

    PSO::ParticleSwarmOptimization<double, Fitness, Compare>
    PSO_Optim(P, G, N, XMin, XMax, VMin, VMax);

    for (unsigned i = 0; i < G; i++) {
        PSO_Optim.run_generation();
    }

    hasRun = true;
}

double Simulation_PSROptimization::Fitness::operator()(
    std::shared_ptr<PSO::PSO_Particle<double>> particle) {

    //Creates a copy of the topology.
    std::shared_ptr<Topology> TopologyCopy(new Topology(*T));

    //Creates the RWA Algorithms
    std::shared_ptr<PowerSeriesRouting> R_Alg(new PowerSeriesRouting(TopologyCopy,
            Simulation_PSROptimization::MasterPSR->get_Costs()));
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg =
        WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
            Simulation_PSROptimization::WavAssign_Algorithm, TopologyCopy);
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg;

    if (Simulation_PSROptimization::Type == TranslucentNetwork) {
        RA_Alg = RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
                     Simulation_PSROptimization::RegAssignment_Algorithm, TopologyCopy);
    } else {
        RA_Alg = nullptr;
    }

    //Initializes routing algorithm with the particle.
    R_Alg->initCoefficients(*particle);

    //Creates the Call Generator and the RWA Object
    std::shared_ptr<CallGenerator> Generator(
        new CallGenerator(
            TopologyCopy, Simulation_PSROptimization::OptimizationLoad,
            TransmissionBitrate::DefaultBitrates));
    std::shared_ptr<RoutingWavelengthAssignment> RWA(
        new RoutingWavelengthAssignment(
            R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, TopologyCopy));

    return
        NetworkSimulation(Generator, RWA, Simulation_PSROptimization::NumCalls).
        get_CallBlockingProbability();
}
