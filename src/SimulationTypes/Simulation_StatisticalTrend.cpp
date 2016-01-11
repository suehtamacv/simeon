#include <SimulationTypes/Simulation_StatisticalTrend.h>
#include <SimulationTypes/NetworkSimulation.h>
#include <Structure/Link.h>
#include <Calls/CallGenerator.h>
#include <RWA/RoutingWavelengthAssignment.h>

Simulation_StatisticalTrend::Simulation_StatisticalTrend() {
    hasLoaded = false;
}

void Simulation_StatisticalTrend::help() {
    std::cout << "\t\tSTATISTICAL TREND SIMULATION" << std::endl << std::endl <<
              "This simulation repeats a fixed-parameter network simulation, "
              "in order to evaluate any statistical trends on the results." << std::endl;
}

void Simulation_StatisticalTrend::load() {
    //Generic readings.
    SimulationType::load();

    std::cout << std::endl << "-> Choose a network type." << std::endl;

    do {
        for (auto &nettype : NetworkTypes.left) {
            std::cout << "(" << nettype.first << ")\t" << nettype.second << std::endl;
        }

        int Net_Type;
        std::cin >> Net_Type;

        if (std::cin.fail() || NetworkTypes.left.count((Network_Type) Net_Type) == 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Network Type." << std::endl;
            std::cout << std::endl << "-> Choose a network type." << std::endl;
        } else {
            Type = (Network_Type) Net_Type;
            break;
        }
    } while (1);

    Node::load();

    Link::load(T);

    //RWA Algorithms
    {
        //Routing Algorithm
        Routing_Algorithm = RoutingAlgorithm::define_RoutingAlgorithm();

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

    std::cout << std::endl << "-> Define the network load." << std::endl;

    do {
        std::cin >> NetworkLoad;

        if (std::cin.fail() || NetworkLoad < 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the network load." << std::endl;
        } else {
            break;
        }
    } while (1);

    std::cout << std::endl << "-> Define the number of iterations." << std::endl;

    do {
        std::cin >> NumRepetitions;

        if (std::cin.fail() || NumRepetitions < 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of repetitions." << std::endl;
            std::cout << std::endl << "-> Define the number of iterations." << std::endl;
        } else {
            break;
        }
    } while (1);

    create_Simulations();

    hasLoaded = true;
}

void Simulation_StatisticalTrend::create_Simulations() {
    if (Type == TranslucentNetwork) {
        place_Regenerators(T);
    }

    for (int i = 0; i < NumRepetitions; i++) {
        //Creates a copy of the topology.
        std::shared_ptr<Topology> TopologyCopy(new Topology(*T));

        //Creates the RWA Algorithms
        std::shared_ptr<RoutingAlgorithm> R_Alg =
            RoutingAlgorithm::create_RoutingAlgorithm(Routing_Algorithm, TopologyCopy);
        std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg =
            WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
                WavAssign_Algorithm, TopologyCopy);
        std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg;

        if (Type == TranslucentNetwork) {
            RA_Alg = RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
                         RegAssignment_Algorithm, TopologyCopy);
        } else {
            RA_Alg = nullptr;
        }

        //Creates the Call Generator and the RWA Object
        std::shared_ptr<CallGenerator> Generator(new CallGenerator(TopologyCopy,
                NetworkLoad));
        std::shared_ptr<RoutingWavelengthAssignment> RWA(
            new RoutingWavelengthAssignment(
                R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, TopologyCopy));

        //Push simulation into stack
        simulations.push_back(
            std::shared_ptr<NetworkSimulation>(new NetworkSimulation(
                    Generator, RWA, NumCalls)));
    }
}

void Simulation_StatisticalTrend::place_Regenerators(
    std::shared_ptr<Topology> T) {

    std::shared_ptr<RoutingAlgorithm> R_Alg =
        RoutingAlgorithm::create_RoutingAlgorithm(
            Routing_Algorithm, T);
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg =
        WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
            WavAssign_Algorithm, T);
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg =
        RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
            RegAssignment_Algorithm, T);
    std::shared_ptr<RoutingWavelengthAssignment> RWA(
        new RoutingWavelengthAssignment(
            R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, T));

    std::shared_ptr<RegeneratorPlacementAlgorithm> RP_Alg =
        RegeneratorPlacementAlgorithm::create_RegeneratorPlacementAlgorithm(
            RegPlacement_Algorithm, T, RWA, NetworkLoad, NumCalls);

    RP_Alg->placeRegenerators();

}

void Simulation_StatisticalTrend::print() {
    if (!hasLoaded) {
        load();
    }

    int Sim = 1;

    std::cout << std::endl << "* * RESULTS * *" << std::endl;
    std::cout << "SIMULATION\tCALL BLOCKING PROBABILITY" << std::endl;

    extern bool parallelism_enabled;
    #pragma omp parallel for ordered schedule(dynamic) if(parallelism_enabled)

    for (unsigned i = 0; i < simulations.size(); i++) {
        simulations[i]->run();

        if (!simulations[i]->hasSimulated) {
            simulations[i]->run();
        }

        #pragma omp ordered
        std::cout << Sim++ << "\t\t" << simulations[i]->get_CallBlockingProbability()
                  << std::endl;
    }
}

void Simulation_StatisticalTrend::save(std::string) {

}

void Simulation_StatisticalTrend::load_file(std::string) {

}

void Simulation_StatisticalTrend::run() {
    if (!hasLoaded) {
        load();
    }

    extern bool parallelism_enabled;
    #pragma omp parallel for ordered schedule(dynamic) if(parallelism_enabled)

    for (unsigned i = 0; i < simulations.size(); i++) {
        simulations[i]->run();
    }
}
