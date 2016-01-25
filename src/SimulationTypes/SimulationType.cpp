#include <SimulationTypes/SimulationType.h>
#include "SimulationTypes.h"
#include <boost/assign.hpp>
#include <boost/assign.hpp>
#include <boost/program_options.hpp>
#include <iostream>

SimulationType::Network_Type SimulationType::Type;

SimulationType::NetworkTypeBimap SimulationType::NetworkTypes =
    boost::assign::list_of<SimulationType::NetworkTypeBimap::relation>
#define X(a,b, c) (a,b)
    NETWORK_TYPE
#undef X
    ;

SimulationType::NetworkTypeNicknameBimap SimulationType::NetworkTypesNicknames =
    boost::assign::list_of<SimulationType::NetworkTypeNicknameBimap::relation>
#define X(a,b, c) (a,c)
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

SimulationType::SimulationType(Simulation_Type SimType) : SimType(SimType)
{

}

void SimulationType::load()
{
    std::cout << std::endl << "-> Choose a topology." << std::endl;

    do
        {
        for (auto &topol : Topology::DefaultTopologiesNames.left)
            {
            std::cout << "(" << topol.first << ")\t" << topol.second << std::endl;
            }

        int Topol;
        std::cin >> Topol;

        if (std::cin.fail() || Topology::DefaultTopologiesNames.left.count(
                    (Topology::DefaultTopologies) Topol) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Topology." << std::endl;
            std::cout << std::endl << "-> Choose a topology." << std::endl;
            }
        else
            {
            Chosen_Topology = (Topology::DefaultTopologies) Topol;
            T = Topology::create_DefaultTopology(Chosen_Topology);
            break;
            }
        }
    while (1);

}

void SimulationType::save(std::string SimConfigFileName)
{
    std::ofstream SimConfigFile(SimConfigFileName,
                               std::ofstream::out | std::ofstream::trunc);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << "  [general]" << std::endl << std::endl;
    SimConfigFile << "  SimulationType = " << SimulationTypeNicknames.left.at(SimType) << std::endl;

}

std::shared_ptr<SimulationType> SimulationType::create()
{
    int option;
    std::cout << std::endl << "-> Select an option. " << std::endl;
    std::cout << "(0)\tStart a new simulation" << std::endl << "(1)\tLoad previous simulation" << std::endl;

    do
    {
        std::cin >> option;

        if (std::cin.fail() ||
                option < 0 || option > 1)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Option." << std::endl;
            std::cout << std:: endl << "-> Select an option. " << std::endl;
            std::cout << "(0)\tStart a new simulation" << std::endl << "(1)\tLoad previous simulation" << std::endl;
            }
        else
        {
            break;
        }
    } while(1);

    if (option == 0)
        return start();

    else if (option == 1)
        return open();
}

std::shared_ptr<SimulationType> SimulationType::start()
{
    std::cout << std::endl << "-> Define a simulation to run." << std::endl;

    do
        {
        for (auto &sim : SimulationTypeNames.left)
            {
            std::cout << "(" << sim.first << ")\t" << sim.second << std::endl;
            }

        int simul;
        std::cin >> simul;

        if (std::cin.fail() ||
                SimulationTypeNames.left.count((Simulation_Type) simul) == 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Simulation Type." << std::endl;
            std::cout << std::endl << "-> Define a simulation to run." << std::endl;
            }
        else
            {
            std::shared_ptr<SimulationType> simulation;

            switch ((Simulation_Type) simul)
                {
                case transparency:
                    simulation = std::make_shared<Simulation_TransparencyAnalysis>();
                    break;

                case morp3o:
                    simulation = std::make_shared<Simulation_NSGA2_RegnPlac>();
                    break;

                case networkload:
                    simulation = std::make_shared<Simulation_NetworkLoad>();
                    break;

                case psroptimization:
                    simulation = std::make_shared<Simulation_PSROptimization>();
                    break;

                case regnum:
                    simulation = std::make_shared<Simulation_RegeneratorNumber>();
                    break;

                case statisticaltrend:
                    simulation = std::make_shared<Simulation_StatisticalTrend>();
                    break;
                }

            simulation->help();
            return simulation;
            }
        }
    while (1);
}

std::shared_ptr<SimulationType> SimulationType::open()
{
    std::string ConfigFileName;
    /*
    std::cout << "-> Enter the file name." << std::endl;
    std::getline(std::cin, SimConfigFile);
    */
    ConfigFileName = "SimConfigFile.ini"; // File with previous simulation configurations

    using namespace boost::program_options;

    options_description ConfigDesctription("Configurations Data");
    ConfigDesctription.add_options()("general.SimulationType",
                                     value<std::string>()->required(), "Simulation Type");

    variables_map VariablesMap;
    std::ifstream ConfigFile(ConfigFileName, std::ifstream::in);
    BOOST_ASSERT_MSG(ConfigFile.is_open(), "Input file is not open");
    store(parse_config_file<char>(ConfigFile, ConfigDesctription, true), VariablesMap);
    ConfigFile.close();
    notify(VariablesMap);

    std::string SimType = VariablesMap["general.SimulationType"].as<std::string>();

    std::shared_ptr<SimulationType> simulation;

    if(SimType == SimulationTypeNicknames.left.at(Simulation_Type::regnum))
    {
        simulation = std::make_shared<Simulation_RegeneratorNumber>();
        simulation->load_file(ConfigFileName);
        return simulation;
    }
    else if(SimType == SimulationTypeNicknames.left.at(Simulation_Type::networkload))
    {
        simulation = std::make_shared<Simulation_NetworkLoad>();
        simulation->load_file(ConfigFileName);
        return simulation;
    }
    else if(SimType == SimulationTypeNicknames.left.at(Simulation_Type::transparency))
    {
        simulation = std::make_shared<Simulation_TransparencyAnalysis>();
        simulation->load_file(ConfigFileName);
        return simulation;
    }
}
