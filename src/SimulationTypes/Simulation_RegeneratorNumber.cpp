#include <SimulationTypes/Simulation_RegeneratorNumber.h>
#include <Structure/Link.h>
#include <Calls/CallGenerator.h>
#include <boost/assert.hpp>
#include <boost/assign.hpp>
#include <boost/program_options.hpp>
#include <map>

Simulation_RegeneratorNumber::Simulation_RegeneratorNumber() :
    SimulationType(Simulation_Type::regnum), hasLoaded(false)
{

}

void Simulation_RegeneratorNumber::help()
{
    std::cout << "\t\tNUMBER OF REGENERATORS" << std::endl << std::endl <<
              "This simulation inserts regenerators in the nodes of the "
              " topology, and analyses the call requisition blocking probability."
              " If the RP Algorithm is NX, then the same number of regenerators"
              " will be inserted in each node. Otherwise, the product N . X is"
              " distributed over the topology." << std::endl;
}

void Simulation_RegeneratorNumber::run()
{
    if (!hasLoaded)
        {
        load();
        }

    extern bool parallelism_enabled;
    #pragma omp parallel for ordered schedule(dynamic) if(parallelism_enabled)

    for (unsigned i = 0; i < simulations.size(); i++)
        {
        if (!simulations[i]->hasSimulated)
            {
            simulations[i]->run();
            }
        }
}

void Simulation_RegeneratorNumber::load()
{
    //General readings
    SimulationType::load();

    Node::load();

    Link::load(T);

    //RWA Algorithms
        {
        //Routing Algorithm
        Routing_Algorithm = RoutingAlgorithm::define_RoutingAlgorithm();

        //Wavelength Assignment Algorithm
        WavAssign_Algorithm =
            WavelengthAssignmentAlgorithm::define_WavelengthAssignmentAlgorithm();

        //Regenerator Placement Algorithm
        RegPlacement_Algorithm =
            RegeneratorPlacementAlgorithm::define_RegeneratorPlacementAlgorithm();

        //Regenerator Assignment Algorithm
        RegAssignment_Algorithm =
            RegeneratorAssignmentAlgorithm::define_RegeneratorAssignmentAlgorithm();
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
        std::cin >> OptimizationLoad;

        if (std::cin.fail() || OptimizationLoad < 0)
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

    std::cout << std::endl <<
              "-> Define the minimum number of regenerators per node"
              << std::endl;

    do
        {
        std::cin >> minRegNumber;

        if (std::cin.fail())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of regenerators." << std::endl;
            std::cout << std::endl <<
                      "-> Define the minimum number of regenerators per node"
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl <<
              "-> Define the maximum number of regenerators per node"
              << std::endl;

    do
        {
        std::cin >> maxRegNumber;

        if (std::cin.fail() || maxRegNumber < minRegNumber)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of regenerators." << std::endl;
            std::cout << std::endl <<
                      "-> Define the maximum number of regenerators per node"
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the number of regenerators per node step"
              << std::endl;

    do
        {
        std::cin >> stepRegNumber;

        if (std::cin.fail())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of regenerators." << std::endl;
            std::cout << std::endl << "-> Define the number of regenerators per node step"
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the number of translucent nodes"
              << std::endl;

    do
        {
        std::cin >> numTranslucentNodes;

        if (std::cin.fail() || numTranslucentNodes > T->Nodes.size())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of translucent nodes."  << std::endl;
            std::cout << std::endl << "-> Define the number of translucent nodes"
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    createSimulations();

    hasLoaded = true;
}

void Simulation_RegeneratorNumber::save(std::string SimConfigFileName)
{
    SimulationType::save(SimConfigFileName);

    Link::save(SimConfigFileName, T);

    std::ofstream SimConfigFile(SimConfigFileName,
                               std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << std::endl << "  [algorithms]" << std::endl << std::endl;
    SimConfigFile << "  RoutingAlgorithm = " << RoutingAlgorithm::RoutingAlgorithmNicknames.left.at(Routing_Algorithm)
                  << std::endl;
    SimConfigFile << "  WavelengthAssignmentAlgorithm = " << WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithmNicknames.left.at(WavAssign_Algorithm)
                  << std::endl;
    SimConfigFile << "  RegeneratorPlacementAlgorithm = " << RegeneratorPlacementAlgorithm::RegeneratorPlacementNicknames.left.at(RegPlacement_Algorithm) << std::endl;
    SimConfigFile << "  RegeneratorAssignmentAlgorithm = " << RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames.left.at(RegAssignment_Algorithm) << std::endl;
    SimConfigFile << std::endl << "  [sim_info]" << std::endl << std::endl;
    SimConfigFile << "  NumCalls = " << NumCalls << std::endl;
    SimConfigFile << "  OptimizationLoad = " << OptimizationLoad << std::endl;
    SimConfigFile << "  minRegNumber = " << minRegNumber << std::endl;
    SimConfigFile << "  maxRegNumber = " << maxRegNumber << std::endl;
    SimConfigFile << "  stepRegNumber = " << stepRegNumber << std::endl;
    SimConfigFile << "  numTranslucentNodes = " << numTranslucentNodes << std::endl;

    SimConfigFile << std::endl;
    T->save(SimConfigFileName);
}

void Simulation_RegeneratorNumber::load_file(std::string ConfigFileName)
{
    using namespace boost::program_options;

    options_description ConfigDesctription("Configurations Data");
    ConfigDesctription.add_options()("general.SimulationType",
                                     value<std::string>()->required(), "Simulation Type")
            ("general.AvgSpanLength", value<long double>()->required(), "Distance Between Inline Amps.")
            ("algorithms.RoutingAlgorithm", value<std::string>()->required(), "Routing Algorithm")
            ("algorithms.WavelengthAssignmentAlgorithm", value<std::string>()->required(), "Wavelength Assignment Algorithm")
            ("algorithms.RegeneratorPlacementAlgorithm", value<std::string>()->required(), "Regenerator Placement Algorithm")
            ("algorithms.RegeneratorAssignmentAlgorithm", value<std::string>()->required(), "Regenerator Assignment Algorithm")
            ("sim_info.NumCalls", value<long double>()->required(), "Number of Calls")
            ("sim_info.OptimizationLoad", value<long double>()->required(), "Network Load")
            ("sim_info.minRegNumber", value<long double>()->required(), "Min. Number of Reg. per Node")
            ("sim_info.maxRegNumber", value<long double>()->required(), "Max. Number of Reg. per Node")
            ("sim_info.stepRegNumber", value<long double>()->required(), "Number of Reg. per Node Step")
            ("sim_info.numTranslucentNodes", value<long double>()->required(), "Number of Translucent Nodes");

    variables_map vm;

    std::ifstream ConfigFile(ConfigFileName, std::ifstream::in);
    BOOST_ASSERT_MSG(ConfigFile.is_open(), "Input file is not open");

    store(parse_config_file<char>(ConfigFile, ConfigDesctription, true), vm);
    ConfigFile.close();
    notify(vm);

    long double AvgSpanLengthValue = vm["general.AvgSpanLength"].as<long double>();
    std::string RoutingAlgorithmValue = vm["algorithms.RoutingAlgorithm"].as<std::string>();
    std::string WavelengthAssignmentAlgorithmValue = vm["algorithms.WavelengthAssignmentAlgorithm"].as<std::string>();
    std::string RegeneratorPlacementAlgorithmValue = vm["algorithms.RegeneratorPlacementAlgorithm"].as<std::string>();
    std::string RegeneratorAssignmentAlgorithmValue = vm["algorithms.RegeneratorAssignmentAlgorithm"].as<std::string>();
    long double NumCallsValue = vm["sim_info.NumCalls"].as<long double>();
    long double OptimizationLoadValue = vm["sim_info.OptimizationLoad"].as<long double>();
    long double minRegNumberValue = vm["sim_info.minRegNumber"].as<long double>();
    long double maxRegNumberValue = vm["sim_info.maxRegNumber"].as<long double>();
    long double stepRegNumberValue = vm["sim_info.stepRegNumber"].as<long double>();
    long double numTranslucentNodesValue = vm["sim_info.numTranslucentNodes"].as<long double>();

    std::cout << "Average Span Length = " << AvgSpanLengthValue << std::endl;
    std::cout << "Routing Algorithm = " << RoutingAlgorithmValue << std::endl;
    std::cout << "Wavelength Assignment Algorithm = " << WavelengthAssignmentAlgorithmValue << std::endl;
    std::cout << "Regenerator Placement Algorithm = " << RegeneratorPlacementAlgorithmValue << std::endl;
    std::cout << "Regenerator Assignment Algorithm = " << RegeneratorAssignmentAlgorithmValue << std::endl;
    std::cout << "Number of Calls = " << NumCallsValue << std::endl;
    std::cout << "Network Load = " << OptimizationLoadValue << std::endl;
    std::cout << "Min. Number of Reg. per Node = " << minRegNumberValue << std::endl;
    std::cout << "Max. Number of Reg. per Node = " << maxRegNumberValue << std::endl;
    std::cout << "Number of Reg. per Node Step = " << stepRegNumberValue << std::endl;
    std::cout << "Number of Translucent Nodes = " << numTranslucentNodesValue << std::endl;

    T = std::shared_ptr<Topology>(new Topology(ConfigFileName));
    Link::DefaultAvgSpanLength = AvgSpanLengthValue;
    T->set_avgSpanLength(AvgSpanLengthValue);
    Routing_Algorithm = RoutingAlgorithm::RoutingAlgorithmNicknames.right.at(RoutingAlgorithmValue);
    WavAssign_Algorithm = WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithmNicknames.right.at(WavelengthAssignmentAlgorithmValue);
    RegPlacement_Algorithm = RegeneratorPlacementAlgorithm::RegeneratorPlacementNicknames.right.at(RegeneratorPlacementAlgorithmValue);
    RegAssignment_Algorithm = RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames.right.at(RegeneratorAssignmentAlgorithmValue);
    NumCalls = NumCallsValue;
    OptimizationLoad = OptimizationLoadValue;
    minRegNumber = minRegNumberValue;
    maxRegNumber = maxRegNumberValue;
    stepRegNumber = stepRegNumberValue;
    numTranslucentNodes = numTranslucentNodesValue;

    createSimulations();

    hasLoaded = true;
}

void Simulation_RegeneratorNumber::print()
{
    if (!hasLoaded)
        {
        load();
        }

    std::cout << std::endl << "* * RESULTS * *" << std::endl;
    std::cout << "NUM REGENERATORS\tCALL BLOCKING PROBABILITY" << std::endl;

    extern bool parallelism_enabled;
    #pragma omp parallel for ordered schedule(dynamic) if(parallelism_enabled)

    for (unsigned i = 0; i < simulations.size(); i++)
        {
        if (!simulations[i]->hasSimulated)
            {
            simulations[i]->run();
            }

        #pragma omp ordered
        std::cout << simulations[i]->Generator->T->get_NumRegenerators() << "\t\t\t"
                  << simulations[i]->get_CallBlockingProbability() << std::endl;

        }

    std::string ConfigFileName = "SimConfigFileTEMP.ini"; // Name of the file

    save(ConfigFileName);
}

void Simulation_RegeneratorNumber::createSimulations()
{
    placeRegenerators(T);

    for (unsigned long nreg = minRegNumber; nreg <= maxRegNumber;
            nreg += stepRegNumber)
        {
        //Creates a copy of the Topology
        std::shared_ptr<Topology> TopologyCopy(new Topology(*T));

        //Reallocates the regenerators
        refreshRegenerators(TopologyCopy, nreg * numTranslucentNodes);

        //Creates the RWA Algorithms
        std::shared_ptr<RoutingAlgorithm> R_Alg =
            RoutingAlgorithm::create_RoutingAlgorithm(Routing_Algorithm, TopologyCopy);

        std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg =
            WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
                WavAssign_Algorithm, TopologyCopy);

        std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg =
            RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
                RegAssignment_Algorithm, TopologyCopy);

        //Creates the Call Generator and the RWA Object
        std::shared_ptr<CallGenerator> Generator(new CallGenerator(TopologyCopy,
                OptimizationLoad));
        std::shared_ptr<RoutingWavelengthAssignment> RWA(
            new RoutingWavelengthAssignment(
                R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, TopologyCopy));

        //Push simulation into stack
        simulations.push_back(
            std::shared_ptr<NetworkSimulation>(new NetworkSimulation(
                    Generator, RWA, NumCalls)));
        }
}

void Simulation_RegeneratorNumber::placeRegenerators(
    std::shared_ptr<Topology> Top)
{
    std::shared_ptr<RoutingAlgorithm> R_Alg =
        RoutingAlgorithm::create_RoutingAlgorithm(
            Routing_Algorithm, Top);
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg =
        WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
            WavAssign_Algorithm, Top);
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg =
        RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
            RegAssignment_Algorithm, Top);
    std::shared_ptr<RoutingWavelengthAssignment> RWA(
        new RoutingWavelengthAssignment(
            R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, Top));

    std::shared_ptr<RegeneratorPlacementAlgorithm> RP_Alg =
        RegeneratorPlacementAlgorithm::create_RegeneratorPlacementAlgorithm(
            RegPlacement_Algorithm, Top, RWA, OptimizationLoad, NumCalls, false);

    if (RP_Alg->isNXAlgorithm)
        {
        RP_Alg->placeRegenerators(numTranslucentNodes, 100);
        }
    else
        {
        RP_Alg->placeRegenerators(numTranslucentNodes * 100);
        }
}

void Simulation_RegeneratorNumber::refreshRegenerators(
    std::shared_ptr<Topology> Top, unsigned long numReg)
{
    unsigned long totalReg = Top->get_NumRegenerators();

    for (auto &node : Top->Nodes)
        {
        unsigned long nodeNumReg = node->get_NumRegenerators();

        if (nodeNumReg != 0)
            {
            node->set_NumRegenerators(std::round(nodeNumReg * numReg / (1.0 * totalReg)));
            }
        }
}
