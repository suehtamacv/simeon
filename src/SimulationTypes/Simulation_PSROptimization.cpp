#include <SimulationTypes/Simulation_PSROptimization.h>
#include <GeneralPurposeAlgorithms/PSO.h>
#include <Structure/Link.h>
#include <RWA.h>

Simulation_PSROptimization::Simulation_PSROptimization() {
    hasLoaded = false;
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

void Simulation_PSROptimization::save(std::ofstream) {

}

void Simulation_PSROptimization::load_file(std::ifstream) {

}

void Simulation_PSROptimization::print() {

}

void Simulation_PSROptimization::run() {
    if (!hasLoaded) {
        load();
    }
}

long double Simulation_PSROptimization::Fitness::operator()(std::shared_ptr<PSO::PSO_Particle<double>> particle) {

    return 1;
}
