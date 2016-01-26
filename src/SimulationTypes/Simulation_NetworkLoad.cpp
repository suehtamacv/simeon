#include <SimulationTypes/Simulation_NetworkLoad.h>
#include <Structure/Topology.h>
#include <Structure/Link.h>
#include <Structure/Node.h>
#include <Calls/CallGenerator.h>
#include <RWA/RoutingWavelengthAssignment.h>
#include <iostream>
#include <boost/assert.hpp>
#include <boost/assign.hpp>
#include <boost/program_options.hpp>
#include <map>

Simulation_NetworkLoad::Simulation_NetworkLoad() : SimulationType(Simulation_Type::networkload)
{
    hasSimulated = hasLoaded = false;

    Routing_Algorithm = (RoutingAlgorithm::RoutingAlgorithms) - 1;
    WavAssign_Algorithm =
        (WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms) - 1;
    RegPlacement_Algorithm =
        (RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms) - 1;
    RegAssignment_Algorithm =
        (RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms) - 1;
}

void Simulation_NetworkLoad::help()
{
    std::cout << "\t\tNETWORK LOAD SIMULATION" << std::endl << std::endl <<
              "This simulation varies the network load, and analyzes the"
              " network performance in terms of predefined metrics, such"
              " as call blocking probability, or slot blocking probability." << std::endl;
}

void Simulation_NetworkLoad::run()
{
    if (!hasLoaded)
    {
        load();
    }

    std::cout << std::endl << "* * RESULTS * *" << std::endl;
    std::cout << "LOAD\tCALL BLOCKING PROBABILITY" << std::endl;

    extern bool parallelism_enabled;
    #pragma omp parallel for ordered schedule(dynamic) if(parallelism_enabled)

    for (unsigned i = 0; i < simulations.size(); i++)
    {
        if (!simulations[i]->hasSimulated)
        {
            simulations[i]->run();
        }

        #pragma omp ordered
        simulations[i]->print();
    }

    std::string ConfigFileName = "SimConfigFile.ini"; // Name of the file

    save(ConfigFileName);
}

void Simulation_NetworkLoad::print()
{
    if (!hasLoaded)
    {
        load();
    }

    std::cout << std::endl << "  A Network Load Variation Simulation is about to start with the following parameters: " << std::endl;
    std::cout << "-> Network Type = " << NetworkTypesNicknames.left.at(Type) << std::endl;
    std::cout << "-> Distance Between Inline Amps. = " << T->AvgSpanLength << std::endl;
    std::cout << "-> Routing Algorithm = " << RoutingAlgorithm::RoutingAlgorithmNicknames.left.at(Routing_Algorithm)
                  << std::endl;
    std::cout << "-> Wavelength Assignment Algorithm = " << WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithmNicknames.left.at(WavAssign_Algorithm)
                  << std::endl;
    if(Type == TranslucentNetwork)
    {
        std::cout << "-> Regenerator Placement Algorithm = " << RegeneratorPlacementAlgorithm::RegeneratorPlacementNicknames.left.at(RegPlacement_Algorithm) << std::endl;
        std::cout << "-> Regenerator Assignment Algorithm = " << RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames.left.at(RegAssignment_Algorithm) << std::endl;
    }
    std::cout << "-> NumCalls = " << NumCalls << std::endl;
    std::cout << "-> NetworkLoadMin = " << NetworkLoadMin << std::endl;
    std::cout << "-> NetworkLoadMax= " << NetworkLoadMax << std::endl;
    std::cout << "-> NetworkLoadStep = " << NetworkLoadStep << std::endl;

    if(Type == TranslucentNetwork)
    {
        std::cout << "-> numTranslucentNodes = " << NX_RegeneratorPlacement::NX_N << std::endl;
        std::cout << "-> numReg = " << NX_RegeneratorPlacement::NX_X << std::endl;
    }
}

void Simulation_NetworkLoad::load()
{
    //Generic readings.
    SimulationType::load();

    std::cout << std::endl << "-> Choose a network type." << std::endl;

    do
    {
        for (auto &nettype : NetworkTypes.left)
        {
            std::cout << "(" << nettype.first << ")\t" << nettype.second << std::endl;
        }

        int Net_Type;
        std::cin >> Net_Type;

        if (std::cin.fail() || NetworkTypes.left.count((Network_Type) Net_Type) == 0)
        {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid Network Type." << std::endl;
            std::cout << std::endl << "-> Choose a network type." << std::endl;
        }
        else
        {
            Type = (Network_Type) Net_Type;
            break;
        }
    }
    while (1);

    Node::load();

    Link::load(T);

    //RWA Algorithms
    {
        //Routing Algorithm
        Routing_Algorithm = RoutingAlgorithm::define_RoutingAlgorithm();

        //Wavelength Assignment Algorithm
        WavAssign_Algorithm =
            WavelengthAssignmentAlgorithm::define_WavelengthAssignmentAlgorithm();

        if (Type == TranslucentNetwork)
        {
            //Regenerator Placement Algorithm
            RegPlacement_Algorithm =
                RegeneratorPlacementAlgorithm::define_RegeneratorPlacementAlgorithm();

            //Regenerator Assignment Algorithm
            RegAssignment_Algorithm =
                RegeneratorAssignmentAlgorithm::define_RegeneratorAssignmentAlgorithm();
        }
    }

    std::cout << std::endl << "-> Define the number of calls." << std::endl;

    do
    {
        std::cin >> NumCalls;

        if (std::cin.fail() || NumCalls < 0)
        {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of calls." << std::endl;
            std::cout << std::endl << "-> Define the number of calls." << std::endl;
        }
        else
        {
            break;
        }
    }
    while (1);

    std::cout << std::endl << "-> Define the minimum network load." << std::endl;

    do
    {
        std::cin >> NetworkLoadMin;

        if (std::cin.fail() || NetworkLoadMin < 0)
        {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the minimum network load." << std::endl;
        }
        else
        {
            break;
        }
    }
    while (1);

    std::cout << std::endl << "-> Define the maximum network load." << std::endl;

    do
    {
        std::cin >> NetworkLoadMax;

        if (std::cin.fail() || NetworkLoadMax < NetworkLoadMin)
        {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the maximum network load." << std::endl;
        }
        else
        {
            break;
        }
    }
    while (1);

    std::cout << std::endl << "-> Define the network load step." << std::endl;

    do
    {
        std::cin >> NetworkLoadStep;

        if (std::cin.fail() || NetworkLoadStep < 0)
        {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the network load step." << std::endl;
        }
        else
        {
            break;
        }
    }
    while (1);

    runLoadNX = true;

    create_Simulations();

    hasLoaded = true;
}

void Simulation_NetworkLoad::save(std::string SimConfigFileName)
{
    SimulationType::save(SimConfigFileName);

    std::ofstream SimConfigFile(SimConfigFileName,
                               std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << "  NetworkType = " << NetworkTypesNicknames.left.at(Type) << std::endl;

    SimConfigFile.close();

    Link::save(SimConfigFileName, T);

    simulations.front()->RWA->R_Alg->save(SimConfigFileName);
    simulations.front()->RWA->WA_Alg->save(SimConfigFileName);
    if(Type == TranslucentNetwork)
    {
        RegeneratorPlacementAlgorithm::save(SimConfigFileName, RegPlacement_Algorithm);
        simulations.front()->RWA->RA_Alg->save(SimConfigFileName);
    }

    SimConfigFile.open(SimConfigFileName,
                               std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << std::endl << "  [sim_info]" << std::endl << std::endl;
    SimConfigFile << "  NumCalls = " << NumCalls << std::endl;
    SimConfigFile << "  NetworkLoadMin = " << NetworkLoadMin << std::endl;
    SimConfigFile << "  NetworkLoadMax= " << NetworkLoadMax << std::endl;
    SimConfigFile << "  NetworkLoadStep = " << NetworkLoadStep << std::endl;

    if(Type == TranslucentNetwork)
    {
        SimConfigFile << "  numTranslucentNodes = " << NX_RegeneratorPlacement::NX_N << std::endl;
        SimConfigFile << "  numReg = " << NX_RegeneratorPlacement::NX_X << std::endl;
    }

    SimConfigFile << std::endl;
    T->save(SimConfigFileName);
}

void Simulation_NetworkLoad::load_file(std::string ConfigFileName)
{
    using namespace boost::program_options;

    options_description ConfigDesctription("Configurations Data");
    ConfigDesctription.add_options()("general.SimulationType",
                                     value<std::string>()->required(), "Simulation Type")
            ("general.NetworkType", value<std::string>()->required(), "Network Type")
            ("general.AvgSpanLength", value<long double>()->required(), "Distance Between Inline Amps.")
            ("algorithms.RoutingAlgorithm", value<std::string>()->required(), "Routing Algorithm")
            ("algorithms.WavelengthAssignmentAlgorithm", value<std::string>()->required(), "Wavelength Assignment Algorithm")
            ("algorithms.RegeneratorPlacementAlgorithm", value<std::string>(), "Regenerator Placement Algorithm")
            ("algorithms.RegeneratorAssignmentAlgorithm", value<std::string>(), "Regenerator Assignment Algorithm")
            ("sim_info.NumCalls", value<long double>()->required(), "Number of Calls")
            ("sim_info.NetworkLoadMin", value<long double>()->required(), "Min. Network Load")
            ("sim_info.NetworkLoadMax", value<long double>()->required(), "Max. Network Load")
            ("sim_info.NetworkLoadStep", value<long double>()->required(), "Network Load Step")
            ("sim_info.numTranslucentNodes", value<long double>(), "Number of Translucent Nodes")
            ("sim_info.numReg", value<long double>(), "Num. of Regenerators per Node");

    variables_map VariablesMap;

    std::ifstream ConfigFile(ConfigFileName, std::ifstream::in);
    BOOST_ASSERT_MSG(ConfigFile.is_open(), "Input file is not open");

    store(parse_config_file<char>(ConfigFile, ConfigDesctription, true), VariablesMap);
    ConfigFile.close();
    notify(VariablesMap);

    T = std::shared_ptr<Topology>(new Topology(ConfigFileName));
    Type = NetworkTypesNicknames.right.at(VariablesMap["general.NetworkType"].as<std::string>());
    Link::DefaultAvgSpanLength = VariablesMap["general.AvgSpanLength"].as<long double>();
    T->set_avgSpanLength(VariablesMap["general.AvgSpanLength"].as<long double>());
    Routing_Algorithm = RoutingAlgorithm::RoutingAlgorithmNicknames.right.at(VariablesMap["algorithms.RoutingAlgorithm"].as<std::string>());
    WavAssign_Algorithm = WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithmNicknames.right.at(VariablesMap["algorithms.WavelengthAssignmentAlgorithm"].as<std::string>());
    if(Type == Network_Type::TranslucentNetwork)
    {
        RegPlacement_Algorithm = RegeneratorPlacementAlgorithm::RegeneratorPlacementNicknames.right.at( VariablesMap["algorithms.RegeneratorPlacementAlgorithm"].as<std::string>());
        RegAssignment_Algorithm = RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames.right.at(VariablesMap["algorithms.RegeneratorAssignmentAlgorithm"].as<std::string>());
        NX_RegeneratorPlacement::NX_N = VariablesMap["sim_info.numTranslucentNodes"].as<long double>();
        NX_RegeneratorPlacement::NX_X = VariablesMap["sim_info.numReg"].as<long double>();
    }
    NumCalls = VariablesMap["sim_info.NumCalls"].as<long double>();
    NetworkLoadMin = VariablesMap["sim_info.NetworkLoadMin"].as<long double>();
    NetworkLoadMax = VariablesMap["sim_info.NetworkLoadMax"].as<long double>();
    NetworkLoadStep = VariablesMap["sim_info.NetworkLoadStep"].as<long double>();

    hasLoaded = true;
    runLoadNX = false;

    create_Simulations();
}

void Simulation_NetworkLoad::create_Simulations()
{
    if (Type == TranslucentNetwork)
    {
        place_Regenerators(T);
    }

    for (double load = NetworkLoadMin; load <= NetworkLoadMax;
            load += NetworkLoadStep)
    {

        //Creates a copy of the topology.
        std::shared_ptr<Topology> TopologyCopy(new Topology(*T));

        //Creates the RWA Algorithms
        std::shared_ptr<RoutingAlgorithm> R_Alg =
            RoutingAlgorithm::create_RoutingAlgorithm(Routing_Algorithm, TopologyCopy);
        std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg =
            WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
                WavAssign_Algorithm, TopologyCopy);
        std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg;

        if (Type == TranslucentNetwork)
        {
            RA_Alg = RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
                         RegAssignment_Algorithm, TopologyCopy);
        }
        else
        {
            RA_Alg = nullptr;
        }

        //Creates the Call Generator and the RWA Object
        std::shared_ptr<CallGenerator> Generator(new CallGenerator(TopologyCopy, load));
        std::shared_ptr<RoutingWavelengthAssignment> RWA(
            new RoutingWavelengthAssignment(
                R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, TopologyCopy));

        //Push simulation into stack
        simulations.push_back(
            std::shared_ptr<NetworkSimulation>(new NetworkSimulation(
                    Generator, RWA, NumCalls)));

    }
}

void Simulation_NetworkLoad::place_Regenerators(std::shared_ptr<Topology> T)
{

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
            RegPlacement_Algorithm, T, RWA, NetworkLoadMin, NumCalls, runLoadNX);

    RP_Alg->placeRegenerators();
}
