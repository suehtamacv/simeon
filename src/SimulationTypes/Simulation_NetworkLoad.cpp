#include <SimulationTypes/Simulation_NetworkLoad.h>
#include <Structure/Topology.h>
#include <iostream>

Simulation_NetworkLoad::Simulation_NetworkLoad() {
    hasSimulated = hasLoaded = false;

    Routing_Algorithm = (RoutingAlgorithm::RoutingAlgorithms) - 1;
    WavAssign_Algorithm =
        (WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms) - 1;
    RegPlacement_Algorithm =
        (RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms) - 1;
    RegAssignment_Algorithm =
        (RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms) - 1;
}

void Simulation_NetworkLoad::help() {
    std::cout << "\t\tNETWORK LOAD SIMULATION" << std::endl << std::endl <<
              "\tThis simulation varies the network load, and analyzes the"
              " network performance in terms of predefined metrics, such"
              " as call blocking probability, or slot blocking probability." << std::endl;
}

void Simulation_NetworkLoad::run() {
    if (!hasLoaded) {
        load();
    }

    for (auto simulation : simulations) {
        simulation->run();
    }
}

void Simulation_NetworkLoad::print() {
    if (!hasLoaded) {
        load();
    }

    std::cout << std::endl << "* * RESULTS * *" << std::endl;
    std::cout << "LOAD\tCALL BLOCKING PROBABILITY" << std::endl;

    for (auto simulation : simulations) {
        if (!simulation->hasSimulated) {
            simulation->run();
        }

        simulation->print();
    }

}

void Simulation_NetworkLoad::load() {
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

    std::cout << std::endl << "-> Define the minimum network load." << std::endl;

    do {
        std::cin >> NetworkLoadMin;

        if (std::cin.fail() || NetworkLoadMin < 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the minimum network load." << std::endl;
        } else {
            break;
        }
    } while (1);

    std::cout << std::endl << "-> Define the maximum network load." << std::endl;

    do {
        std::cin >> NetworkLoadMax;

        if (std::cin.fail() || NetworkLoadMax < NetworkLoadMin) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the maximum network load." << std::endl;
        } else {
            break;
        }
    } while (1);

    std::cout << std::endl << "-> Define the network load step." << std::endl;

    do {
        std::cin >> NetworkLoadStep;

        if (std::cin.fail() || NetworkLoadStep < 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the network load step." << std::endl;
        } else {
            break;
        }
    } while (1);

    create_Simulations();

    hasLoaded = true;
}

void Simulation_NetworkLoad::save(std::string) {

}

void Simulation_NetworkLoad::load_file(std::string) {
    hasLoaded = true;
}

void Simulation_NetworkLoad::create_Simulations() {
    if (Type == TranslucentNetwork) {
        place_Regenerators(T);
    }

    for (double load = NetworkLoadMin; load <= NetworkLoadMax;
            load += NetworkLoadStep) {

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
        std::shared_ptr<CallGenerator> Generator(
            new CallGenerator(
                TopologyCopy, load, TransmissionBitrate::DefaultBitrates));
        std::shared_ptr<RoutingWavelengthAssignment> RWA(
            new RoutingWavelengthAssignment(
                R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, TopologyCopy));

        //Push simulation into stack
        simulations.push_back(
            std::shared_ptr<NetworkSimulation>(new NetworkSimulation(
                    Generator, RWA, NumCalls)));

    }
}

void Simulation_NetworkLoad::place_Regenerators(std::shared_ptr<Topology> T) {

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
            RegPlacement_Algorithm, T, RWA, NetworkLoadMin, NumCalls);

    RP_Alg->placeRegenerators();
}
