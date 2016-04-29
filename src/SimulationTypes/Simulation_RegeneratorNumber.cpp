#include <SimulationTypes/Simulation_RegeneratorNumber.h>
#include <Structure/Link.h>
#include <Calls/CallGenerator.h>
#include <boost/assert.hpp>
#include <boost/assign.hpp>
#include <boost/program_options.hpp>
#include <map>

using namespace RMSA;
using namespace Simulations;
using namespace ROUT;
using namespace SA;
using namespace RA;
using namespace RP;

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

    std::cout << std::endl << "* * RESULTS * *" << std::endl;
    std::cout << "NUM REGENERATORS\tCALL BLOCKING PROBABILITY" << std::endl;

    std::ofstream OutFile(FileName.c_str());

    extern bool parallelism_enabled;
    #pragma omp parallel for ordered schedule(dynamic) if(parallelism_enabled)

    for (unsigned i = 0; i < simulations.size(); i++)
        {
        if (!simulations[i]->hasSimulated)
            {
            simulations[i]->run();
            }

        #pragma omp ordered
            {
            std::cout << simulations[i]->Generator->T->get_NumRegenerators() << "\t\t\t"
                      << simulations[i]->get_CallBlockingProbability() << std::endl;
            OutFile << simulations[i]->Generator->T->get_NumRegenerators() << "\t"
                    << simulations[i]->get_CallBlockingProbability() << "\t"
                    << simulations[i]->Generator->T->get_NumTranslucentNodes() << std::endl;
            }

        }

    // Saving Sim. Configurations
    std::string ConfigFileName = "SimConfigFile.ini"; // Name of the file
    save(ConfigFileName);
}

void Simulation_RegeneratorNumber::load()
{
    //General readings
    SimulationType::load();

    Node::load();

    Link::load(T);

    //RMSA Algorithms
        {
        //Routing Algorithm
        Routing_Algorithm = RoutingAlgorithm::define_RoutingAlgorithm();

        //Routing Cost
        Routing_Cost = RoutingCost::define_RoutingCost();

        //Wavelength Assignment Algorithm
        WavAssign_Algorithm =
            SA::SpectrumAssignmentAlgorithm::define_SpectrumAssignmentAlgorithm();

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

    createSimulations();

    hasLoaded = true;
}

void Simulation_RegeneratorNumber::save(std::string SimConfigFileName)
{
    SimulationType::save(SimConfigFileName);
    Link::save(SimConfigFileName, T);

    simulations.front()->RMSA->R_Alg->save(SimConfigFileName);
    simulations.front()->RMSA->WA_Alg->save(SimConfigFileName);
    RegeneratorPlacementAlgorithm::save(SimConfigFileName, RegPlacement_Algorithm);
    simulations.front()->RMSA->RA_Alg->save(SimConfigFileName);

    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

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
    ("general.AvgSpanLength", value<long double>()->required(),
     "Distance Between Inline Amps.")
    ("algorithms.RoutingAlgorithm", value<std::string>()->required(),
     "Routing Algorithm")
    ("algorithms.WavelengthAssignmentAlgorithm", value<std::string>()->required(),
     "Wavelength Assignment Algorithm")
    ("algorithms.RegeneratorPlacementAlgorithm", value<std::string>()->required(),
     "Regenerator Placement Algorithm")
    ("algorithms.RegeneratorAssignmentAlgorithm", value<std::string>()->required(),
     "Regenerator Assignment Algorithm")
    ("sim_info.NumCalls", value<long double>()->required(), "Number of Calls")
    ("sim_info.OptimizationLoad", value<long double>()->required(), "Network Load")
    ("sim_info.minRegNumber", value<long double>()->required(),
     "Min. Number of Reg. per Node")
    ("sim_info.maxRegNumber", value<long double>()->required(),
     "Max. Number of Reg. per Node")
    ("sim_info.stepRegNumber", value<long double>()->required(),
     "Number of Reg. per Node Step")
    ("sim_info.numTranslucentNodes", value<long double>()->required(),
     "Number of Translucent Nodes");

    variables_map VariablesMap;

    std::ifstream ConfigFile(ConfigFileName, std::ifstream::in);
    BOOST_ASSERT_MSG(ConfigFile.is_open(), "Input file is not open");

    store(parse_config_file<char>(ConfigFile, ConfigDesctription, true),
          VariablesMap);
    ConfigFile.close();
    notify(VariablesMap);

    T = std::shared_ptr<Topology>(new Topology(ConfigFileName));
    Link::DefaultAvgSpanLength =
        VariablesMap["general.AvgSpanLength"].as<long double>();
    T->set_avgSpanLength(VariablesMap["general.AvgSpanLength"].as<long double>());
    Routing_Algorithm = RoutingAlgorithm::RoutingAlgorithmNicknames.right.at(
                            VariablesMap["algorithms.RoutingAlgorithm"].as<std::string>());
    WavAssign_Algorithm =
        SA::SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithmNicknames.right.at(
            VariablesMap["algorithms.WavelengthAssignmentAlgorithm"].as<std::string>());
    RegPlacement_Algorithm =
        RegeneratorPlacementAlgorithm::RegeneratorPlacementNicknames.right.at(
            VariablesMap["algorithms.RegeneratorPlacementAlgorithm"].as<std::string>());
    RegAssignment_Algorithm =
        RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames.right.at(
            VariablesMap["algorithms.RegeneratorAssignmentAlgorithm"].as<std::string>());
    NumCalls = VariablesMap["sim_info.NumCalls"].as<long double>();
    OptimizationLoad = VariablesMap["sim_info.OptimizationLoad"].as<long double>();
    minRegNumber = VariablesMap["sim_info.minRegNumber"].as<long double>();
    maxRegNumber = VariablesMap["sim_info.maxRegNumber"].as<long double>();
    stepRegNumber = VariablesMap["sim_info.stepRegNumber"].as<long double>();
    numTranslucentNodes =
        VariablesMap["sim_info.numTranslucentNodes"].as<long double>();

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

    createSimulations();

    hasLoaded = true;
}

void Simulation_RegeneratorNumber::print()
{
    if (!hasLoaded)
        {
        load();
        }

    std::cout << std::endl <<
              "  A Number of Regenerators Simulation is about to start with the following parameters: "
              << std::endl;
    std::cout << "-> Metrics =" << std::endl;
    for(auto &metric : Metrics)
        {
        std::cout << "\t-> " << SimulationType::MetricTypes.left.at(
                      metric) << std::endl;
        }
    if(considerFilterImperfection)
        {
        std::cout << "-> Tx Filter Order = " << SpectralDensity::TxFilterOrder <<
                  std::endl;
        std::cout << "-> Gaussian Filter Order = " << SpectralDensity::GaussianOrder <<
                  std::endl;
        }
    std::cout << "-> Distance Between Inline Amplifiers = " << T->AvgSpanLength <<
              std::endl;
    std::cout << "-> Routing Algorithm = " <<
              RoutingAlgorithm::RoutingAlgorithmNames.left.at(Routing_Algorithm)
              << std::endl;
    std::cout << "-> Routing Cost = " <<
              RoutingCost::RoutingCostsNames.left.at(Routing_Cost)
              << std::endl;
    std::cout << "-> Wavelength Assignment Algorithm = " <<
              SA::SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithmNames.left.at(
                  WavAssign_Algorithm)
              << std::endl;
    std::cout << "-> Regenerator Placement Algorithm = " <<
              RegeneratorPlacementAlgorithm::RegeneratorPlacementNames.left.at(
                  RegPlacement_Algorithm) << std::endl;
    std::cout << "-> Regenerator Assignment Algorithm = " <<
              RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNames.left.at(
                  RegAssignment_Algorithm) << std::endl;
    std::cout << "-> Number of Calls = " << NumCalls << std::endl;
    std::cout << "-> Network Load = " << OptimizationLoad << std::endl;
    std::cout << "-> Min. Number of Reg. per Node = " << minRegNumber << std::endl;
    std::cout << "-> Max. Number of Reg. per Node = " << maxRegNumber << std::endl;
    std::cout << "-> Number of Translucent Nodes = " << numTranslucentNodes
              << std::endl;
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

        //Creates the RMSA Algorithms
        std::shared_ptr<RoutingAlgorithm> R_Alg =
            RoutingAlgorithm::create_RoutingAlgorithm(Routing_Algorithm, Routing_Cost,
                    TopologyCopy);

        std::shared_ptr<SA::SpectrumAssignmentAlgorithm> WA_Alg =
            SA::SpectrumAssignmentAlgorithm::create_SpectrumAssignmentAlgorithm(
                WavAssign_Algorithm, TopologyCopy);

        std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg =
            RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
                RegAssignment_Algorithm, TopologyCopy);

        //Creates the Call Generator and the RMSA Object
        std::shared_ptr<CallGenerator> Generator(new CallGenerator(TopologyCopy,
                OptimizationLoad));
        std::shared_ptr<RoutingWavelengthAssignment> RMSA(
            new RoutingWavelengthAssignment(
                R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, TopologyCopy));

        if (!simulations.empty() &&
                Generator->T->get_NumRegenerators() ==
                simulations.back()->Generator->T->get_NumRegenerators())
            {
            //If RP is setting a low number of regenerators, adjancent simulations
            //might have the same number of regenerators. This conditional avoids
            //repeated simulations.
            continue;
            }

        //Push simulation into stack
        simulations.push_back(
            std::shared_ptr<NetworkSimulation>(new NetworkSimulation(
                    Generator, RMSA, NumCalls)));
        }
}

void Simulation_RegeneratorNumber::placeRegenerators(
    std::shared_ptr<Topology> Top)
{
    std::shared_ptr<RoutingAlgorithm> R_Alg =
        RoutingAlgorithm::create_RoutingAlgorithm(
            Routing_Algorithm, Routing_Cost, Top);
    std::shared_ptr<SA::SpectrumAssignmentAlgorithm> WA_Alg =
        SA::SpectrumAssignmentAlgorithm::create_SpectrumAssignmentAlgorithm(
            WavAssign_Algorithm, Top);
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg =
        RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
            RegAssignment_Algorithm, Top);
    std::shared_ptr<RoutingWavelengthAssignment> RMSA(
        new RoutingWavelengthAssignment(
            R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, Top));

    std::shared_ptr<RegeneratorPlacementAlgorithm> RP_Alg =
        RegeneratorPlacementAlgorithm::create_RegeneratorPlacementAlgorithm(
            RegPlacement_Algorithm, Top, RMSA, OptimizationLoad, NumCalls, false);

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
