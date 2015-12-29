#include <SimulationTypes/SimulationType.h>
#include "SimulationTypes.h"
#include <boost/assign.hpp>
#include <iostream>

SimulationType::Network_Type SimulationType::Type;

SimulationType::NetworkTypeBimap SimulationType::NetworkTypes =
    boost::assign::list_of<SimulationType::NetworkTypeBimap::relation>
#define X(a,b) (a,b)
    NETWORK_TYPE
#undef X
#undef NETWORK_TYPE
    ;

SimulationType::SimulationTypeNameBimap SimulationType::SimulationTypeNames =
    boost::assign::list_of<SimulationType::SimulationTypeNameBimap::relation>
#define X(a,b,c) (a,b)
    SIMULATION_TYPE
#undef X
    ;

SimulationType::SimulationTypeNicknameBimap
SimulationType::SimulationTypeNicknames =
    boost::assign::list_of<SimulationType::SimulationTypeNicknameBimap::relation>
#define X(a,b,c) (a,c)
    SIMULATION_TYPE
#undef X
#undef SIMULATION_TYPE
    ;

void SimulationType::load() {
    std::cout << std::endl << "-> Choose a topology." << std::endl;

    do {
        for (auto &topol : Topology::DefaultTopologiesNames.left) {
            std::cout << "(" << topol.first << ")\t" << topol.second << std::endl;
        }

        int Topol;
        std::cin >> Topol;

        if (std::cin.fail() || Topology::DefaultTopologiesNames.left.count(
                    (Topology::DefaultTopologies) Topol) == 0) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Topology." << std::endl;
            std::cout << std::endl << "-> Choose a topology." << std::endl;
        } else {
            Chosen_Topology = (Topology::DefaultTopologies) Topol;
            T = Topology::create_DefaultTopology(Chosen_Topology);
            break;
        }
    } while (1);

}

std::shared_ptr<SimulationType> SimulationType::create() {
    std::cout << std::endl << "-> Define a simulation to run." << std::endl;

    do {
        for (auto &sim : SimulationTypeNames.left) {
            std::cout << "(" << sim.first << ")\t" << sim.second << std::endl;
        }

        int simul;
        std::cin >> simul;

        if (std::cin.fail() ||
                SimulationTypeNames.left.count((Simulation_Type) simul) == 0)  {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Simulation Type." << std::endl;
            std::cout << std::endl << "-> Define a simulation to run." << std::endl;
        } else {
            std::shared_ptr<SimulationType> simulation;

            switch ((Simulation_Type) simul) {
                case networkload:
                    simulation = std::shared_ptr<SimulationType>(new Simulation_NetworkLoad());
                    break;

                case psroptimization:
                    simulation = std::shared_ptr<SimulationType>(new Simulation_PSROptimization());
                    break;

                case statisticaltrend:
                    simulation = std::shared_ptr<SimulationType>(new Simulation_StatisticalTrend());
                    break;
            }

            simulation->help();
            return simulation;
        }
    } while (1);
}
