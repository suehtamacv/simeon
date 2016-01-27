#include <SimulationTypes/Simulation_StatisticalTrend.h>
#include <SimulationTypes/NetworkSimulation.h>
#include <Structure/Link.h>
#include <Calls/CallGenerator.h>
#include <RWA/RoutingWavelengthAssignment.h>
#include <boost/assert.hpp>
#include <boost/assign.hpp>
#include <boost/program_options.hpp>
#include <map>

Simulation_StatisticalTrend::Simulation_StatisticalTrend() : SimulationType(
        Simulation_Type::statisticaltrend)
{
    hasLoaded = false;
}

void Simulation_StatisticalTrend::help()
{
    std::cout << "\t\tSTATISTICAL TREND SIMULATION" << std::endl << std::endl <<
              "This simulation repeats a fixed-parameter network simulation, "
              "in order to evaluate any statistical trends on the results." << std::endl;
}

void Simulation_StatisticalTrend::load()
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

    std::cout << std::endl << "-> Define the network load." << std::endl;

    do
        {
        std::cin >> NetworkLoad;

        if (std::cin.fail() || NetworkLoad < 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the network load." << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the number of iterations." << std::endl;

    do
        {
        std::cin >> NumRepetitions;

        if (std::cin.fail() || NumRepetitions < 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of repetitions." << std::endl;
            std::cout << std::endl << "-> Define the number of iterations." << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the file where to store the results."
              << std::endl;
    do
        {
        std::cin >> FileName;

        if (std::cin.fail())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid filename." << std::endl;
            std::cout << std::endl << "-> Define the file where to store the results."
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    create_Simulations();

    hasLoaded = true;
    runLoadNX = true;
}

void Simulation_StatisticalTrend::create_Simulations()
{
    if (Type == TranslucentNetwork)
        {
        place_Regenerators(T);
        }

    for (int i = 0; i < NumRepetitions; i++)
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
    std::shared_ptr<Topology> T)
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
            RegPlacement_Algorithm, T, RWA, NetworkLoad, NumCalls, runLoadNX);

    RP_Alg->placeRegenerators();

}

void Simulation_StatisticalTrend::print()
{
    if (!hasLoaded)
        {
        load();
        }

    std::cout << std::endl <<
              "  A Statistical Trend Analysis Simulation is about to start with the following parameters: "
              << std::endl;
    std::cout << "-> Network Type = " << NetworkTypesNicknames.left.at(
                  Type) << std::endl;
    std::cout << "-> Distance Between Inline Amps. = " << T->AvgSpanLength <<
              std::endl;
    std::cout << "-> Routing Algorithm = " <<
              RoutingAlgorithm::RoutingAlgorithmNicknames.left.at(Routing_Algorithm)
              << std::endl;
    std::cout << "-> Wavelength Assignment Algorithm = " <<
              WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithmNicknames.left.at(
                  WavAssign_Algorithm)
              << std::endl;
    if(Type == TranslucentNetwork)
        {
        std::cout << "-> Regenerator Placement Algorithm = " <<
                  RegeneratorPlacementAlgorithm::RegeneratorPlacementNicknames.left.at(
                      RegPlacement_Algorithm) << std::endl;
        std::cout << "-> Regenerator Assignment Algorithm = " <<
                  RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames.left.at(
                      RegAssignment_Algorithm) << std::endl;
        }
    std::cout << "-> NumCalls = " << NumCalls << std::endl;
    std::cout << "-> NetworkLoad = " << NetworkLoad << std::endl;
    std::cout << "-> NumRepetitions = " << NumRepetitions << std::endl;
    if(Type == TranslucentNetwork)
        {
        std::cout << "-> numTranslucentNodes = " << NX_RegeneratorPlacement::NX_N <<
                  std::endl;
        std::cout << "-> numReg = " << NX_RegeneratorPlacement::NX_X << std::endl;
        }
}

void Simulation_StatisticalTrend::save(std::string SimConfigFileName)
{
    SimulationType::save(SimConfigFileName);

    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << "  NetworkType = " << NetworkTypesNicknames.left.at(
                      Type) << std::endl;
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
    SimConfigFile << "  NetworkLoad = " << NetworkLoad << std::endl;
    SimConfigFile << "  NumRepetitions = " << NumRepetitions << std::endl;

    if(Type == TranslucentNetwork)
        {
        SimConfigFile << "  numTranslucentNodes = " << NX_RegeneratorPlacement::NX_N <<
                      std::endl;
        SimConfigFile << "  numReg = " << NX_RegeneratorPlacement::NX_X << std::endl;
        }

    SimConfigFile << std::endl;
    T->save(SimConfigFileName);
}

void Simulation_StatisticalTrend::load_file(std::string ConfigFileName)
{
    using namespace boost::program_options;

    options_description ConfigDesctription("Configurations Data");
    ConfigDesctription.add_options()("general.SimulationType",
                                     value<std::string>()->required(), "Simulation Type")
    ("general.NetworkType", value<std::string>()->required(), "Network Type")
    ("general.AvgSpanLength", value<long double>()->required(),
     "Distance Between Inline Amps.")
    ("algorithms.RoutingAlgorithm", value<std::string>()->required(),
     "Routing Algorithm")
    ("algorithms.WavelengthAssignmentAlgorithm", value<std::string>()->required(),
     "Wavelength Assignment Algorithm")
    ("algorithms.RegeneratorPlacementAlgorithm", value<std::string>(),
     "Regenerator Placement Algorithm")
    ("algorithms.RegeneratorAssignmentAlgorithm", value<std::string>(),
     "Regenerator Assignment Algorithm")
    ("sim_info.NumCalls", value<long double>()->required(), "Number of Calls")
    ("sim_info.NetworkLoad", value<long double>()->required(), "Network Load")
    ("sim_info.NumRepetitions", value<long double>()->required(),
     "Number of Repetitions")
    ("sim_info.numTranslucentNodes", value<long double>(),
     "Number of Translucent Nodes")
    ("sim_info.numReg", value<long double>(), "Num. of Regenerators per Node");

    variables_map VariablesMap;

    std::ifstream ConfigFile(ConfigFileName, std::ifstream::in);
    BOOST_ASSERT_MSG(ConfigFile.is_open(), "Input file is not open");

    store(parse_config_file<char>(ConfigFile, ConfigDesctription, true),
          VariablesMap);
    ConfigFile.close();
    notify(VariablesMap);

    T = std::shared_ptr<Topology>(new Topology(ConfigFileName));
    Type = NetworkTypesNicknames.right.at(
               VariablesMap["general.NetworkType"].as<std::string>());
    Link::DefaultAvgSpanLength =
        VariablesMap["general.AvgSpanLength"].as<long double>();
    T->set_avgSpanLength(VariablesMap["general.AvgSpanLength"].as<long double>());
    Routing_Algorithm = RoutingAlgorithm::RoutingAlgorithmNicknames.right.at(
                            VariablesMap["algorithms.RoutingAlgorithm"].as<std::string>());
    WavAssign_Algorithm =
        WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithmNicknames.right.at(
            VariablesMap["algorithms.WavelengthAssignmentAlgorithm"].as<std::string>());
    if(Type == Network_Type::TranslucentNetwork)
        {
        RegPlacement_Algorithm =
            RegeneratorPlacementAlgorithm::RegeneratorPlacementNicknames.right.at(
                VariablesMap["algorithms.RegeneratorPlacementAlgorithm"].as<std::string>());
        RegAssignment_Algorithm =
            RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames.right.at(
                VariablesMap["algorithms.RegeneratorAssignmentAlgorithm"].as<std::string>());
        NX_RegeneratorPlacement::NX_N =
            VariablesMap["sim_info.numTranslucentNodes"].as<long double>();
        NX_RegeneratorPlacement::NX_X =
            VariablesMap["sim_info.numReg"].as<long double>();
        }
    NumCalls = VariablesMap["sim_info.NumCalls"].as<long double>();
    NetworkLoad = VariablesMap["sim_info.NetworkLoad"].as<long double>();
    NumRepetitions = VariablesMap["sim_info.NumRepetitions"].as<long double>();

    runLoadNX = false;
    hasLoaded = true;

    create_Simulations();
}

void Simulation_StatisticalTrend::run()
{
    if (!hasLoaded)
        {
        load();
        }

    int Sim = 1;
    std::ofstream ResultFile(FileName.c_str());

    std::cout << std::endl << "* * RESULTS * *" << std::endl;
    std::cout << "SIMULATION\tCALL BLOCKING PROBABILITY" << std::endl;

    extern bool parallelism_enabled;
    #pragma omp parallel for ordered schedule(dynamic) if(parallelism_enabled)

    for (unsigned i = 0; i < simulations.size(); i++)
        {
        simulations[i]->run();

        if (!simulations[i]->hasSimulated)
            {
            simulations[i]->run();
            }

        #pragma omp ordered
            {
            std::cout << Sim << "\t\t" << simulations[i]->get_CallBlockingProbability()
                      << std::endl;
            ResultFile << Sim++ << "\t\t" << simulations[i]->get_CallBlockingProbability()
                       << std::endl;
            }
        }

    ResultFile.close();

    std::string ConfigFileName = "SimConfigFile.ini"; // Name of the file

    save(ConfigFileName);
}
