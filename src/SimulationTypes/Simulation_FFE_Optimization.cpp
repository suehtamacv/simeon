#include "include/SimulationTypes/Simulation_FFE_Optimization.h"
#include "Structure.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_GA.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Generation.h"
#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FFE_Individual.h"
#include <boost/program_options.hpp>

using namespace Simulations;
using namespace RMSA;

Simulation_FFE_Optimization::Simulation_FFE_Optimization() :
    SimulationType(ffeoptimization)
{
    hasLoaded = false;
}

void Simulation_FFE_Optimization::help()
{
    std::cout << "\t\tEVOLUTIONARY FIRST FIT OPTIMIZATION" << std::endl << std::endl
              <<
              "This simulation runs a genetic algorithm to find the optimized order"
              " of slots to the evolutionary first fit spectrum assignment "
              " algorithm." << std::endl;
}

void Simulation_FFE_Optimization::run()
{
    if (!hasLoaded)
        {
        load();
        }

    auto FFE_GA_Optimization = std::make_shared<SA::FFE::FFE_GA>(*this);

    std::cout << std::endl << "* * RESULTS * *" << std::endl;
    std::cout << "BEST PARTICLE OF I-TH EPOCH" << std::endl;

    for (unsigned g = 1; g <= SA::FFE::FFE_GA::numGen; ++g)
        {
        FFE_GA_Optimization->run_Generation();

        std::cout << std::endl << "EPOCH " << g << std::endl;
        FFE_GA_Optimization->evolution.at(g - 1)->print("NO_FILE_GIVEN");
        FFE_GA_Optimization->evolution.at(g - 1)->print
        (CoefficientsFilename + "_G" + std::to_string(g));
        }

    // Saving Sim. Configurations
    std::string ConfigFileName = "SimConfigFile.ini"; // Name of the file
    save(ConfigFileName);

}

void Simulation_FFE_Optimization::load()
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

    //RMSA Algorithms
        {
        //Routing Algorithm
        Routing_Algorithm = ROUT::RoutingAlgorithm::define_RoutingAlgorithm();

        //Routing Cost
        Routing_Cost = ROUT::RoutingCost::define_RoutingCost();

        if (Type == TranslucentNetwork)
            {
            //Regenerator Placement Algorithm
            RegPlacement_Algorithm =
                RP::RegeneratorPlacementAlgorithm::define_RegeneratorPlacementAlgorithm();

            //Regenerator Assignment Algorithm
            RegAssignment_Algorithm =
                RA::RegeneratorAssignmentAlgorithm::define_RegeneratorAssignmentAlgorithm();
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

    std::cout << std::endl << "-> Define the optimization network load."
              << std::endl;

    do
        {
        std::cin >> OptimizationLoad;

        if (std::cin.fail() || OptimizationLoad < 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the optimization network load." <<
                      std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the file where to store the coefficients."
              << std::endl;

    do
        {
        std::cin >> CoefficientsFilename;

        if (std::cin.fail())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid filename." << std::endl;
            std::cout << std::endl << "-> Define the file where to store the coefficients."
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the file where to log the optimization."
              << std::endl;

    do
        {
        std::cin >> LogFilename;

        if (std::cin.fail() || LogFilename == CoefficientsFilename)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid filename." << std::endl;
            std::cout << std::endl << "-> Define the file where to log the optimization."
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    hasLoaded = true;
}

void Simulation_FFE_Optimization::save(std::string SimConfigFileName)
{
    SimulationType::save(SimConfigFileName);

    std::ofstream SimConfigFile(SimConfigFileName,
                                std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << "  NetworkType = " << NetworkTypesNicknames.left.at(
                      Type) << std::endl;
    SimConfigFile.close();

    Link::save(SimConfigFileName, T);

    ROUT::RoutingAlgorithm::create_RoutingAlgorithm
    (Routing_Algorithm, Routing_Cost, T, false)->save(SimConfigFileName);
    if(Type == TranslucentNetwork)
        {
        RP::RegeneratorPlacementAlgorithm::save(SimConfigFileName,
                                                RegPlacement_Algorithm);
        RA::RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
            RegAssignment_Algorithm, T)->save(SimConfigFileName);
        }

    SimConfigFile.open(SimConfigFileName,
                       std::ofstream::out | std::ofstream::app);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << std::endl << "  [sim_info]" << std::endl << std::endl;
    SimConfigFile << "  NumCalls = " << NumCalls << std::endl;
    SimConfigFile << "  NetworkLoad = " << OptimizationLoad << std::endl;
    SimConfigFile << std::endl;
    T->save(SimConfigFileName);
}

void Simulation_FFE_Optimization::load_file(std::string ConfigFileName)
{
    using namespace boost::program_options;

    options_description ConfigDesctription("Configurations Data");
    ConfigDesctription.add_options()("general.SimulationType",
                                     value<std::string>()->required(), "Simulation Type")
    ("general.AvgSpanLength", value<long double>()->required(),
     "Distance Between Inline Amps.")
    ("algorithms.RoutingAlgorithm", value<std::string>()->required(),
     "Routing Algorithm")
    ("algorithms.RoutingCost", value<std::string>()->required(),
     "Routing Cost")
    ("algorithms.RegeneratorPlacementAlgorithm", value<std::string>()->required(),
     "Regenerator Placement Algorithm")
    ("algorithms.RegeneratorAssignmentAlgorithm", value<std::string>()->required(),
     "Regenerator Assignment Algorithm")
    ("sim_info.NumCalls", value<long double>()->required(), "Number of Calls")
    ("sim_info.OptimizationLoad", value<long double>()->required(), "Network Load");

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
    Routing_Algorithm = ROUT::RoutingAlgorithm::RoutingAlgorithmNicknames.right.at(
                            VariablesMap["algorithms.RoutingAlgorithm"].as<std::string>());
    Routing_Cost = ROUT::RoutingCost::RoutingCostsNicknames.right.at(
                       VariablesMap["algorithms.RoutingCost"].as<std::string>());
    RegPlacement_Algorithm =
        RP::RegeneratorPlacementAlgorithm::RegeneratorPlacementNicknames.right.at(
            VariablesMap["algorithms.RegeneratorPlacementAlgorithm"].as<std::string>());
    RegAssignment_Algorithm =
        RA::RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames.right.at(
            VariablesMap["algorithms.RegeneratorAssignmentAlgorithm"].as<std::string>());
    NumCalls = VariablesMap["sim_info.NumCalls"].as<long double>();
    OptimizationLoad = VariablesMap["sim_info.OptimizationLoad"].as<long double>();

    std::cout << std::endl << "-> Define the file where to store the results."
              << std::endl;
    std::cout << std::endl << "-> Define the file where to store the coefficients."
              << std::endl;

    do
        {
        std::cin >> CoefficientsFilename;

        if (std::cin.fail())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid filename." << std::endl;
            std::cout << std::endl << "-> Define the file where to store the coefficients."
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the file where to log the optimization."
              << std::endl;

    do
        {
        std::cin >> LogFilename;

        if (std::cin.fail() || LogFilename == CoefficientsFilename)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid filename." << std::endl;
            std::cout << std::endl << "-> Define the file where to log the optimization."
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    hasLoaded = true;
}

void Simulation_FFE_Optimization::print()
{
    if (!hasLoaded)
        {
        load();
        }

    std::cout << std::endl <<
              "  A Evolutionary First Fit GA Optimization Simulation is about to start with the following parameters: "
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
    std::cout << "-> Network Type = " << NetworkTypesNicknames.left.at(
                  Type) << std::endl;
    std::cout << "-> Distance Between Inline Amplifiers = " << T->AvgSpanLength <<
              std::endl;
    std::cout << "-> Routing Algorithm = " <<
              ROUT::RoutingAlgorithm::RoutingAlgorithmNames.left.at(Routing_Algorithm)
              << std::endl;
    std::cout << "-> Routing Cost = " <<
              ROUT::RoutingCost::RoutingCostsNames.left.at(Routing_Cost)
              << std::endl;
    if(Type == TranslucentNetwork)
        {
        std::cout << "-> Regenerator Placement Algorithm = " <<
                  RP::RegeneratorPlacementAlgorithm::RegeneratorPlacementNames.left.at(
                      RegPlacement_Algorithm) << std::endl;
        std::cout << "-> Regenerator Assignment Algorithm = " <<
                  RA::RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNames.left.at(
                      RegAssignment_Algorithm) << std::endl;
        }

    std::cout << "-> Number of Calls = " << NumCalls << std::endl;
    std::cout << "-> Network Load = " << OptimizationLoad << std::endl;

    T->print();
}

void Simulation_FFE_Optimization::place_Regenerators
(std::shared_ptr<Topology> T)
{
    std::shared_ptr<ROUT::RoutingAlgorithm> R_Alg =
        ROUT::RoutingAlgorithm::create_RoutingAlgorithm(
            Routing_Algorithm, Routing_Cost, T);
    std::shared_ptr<SA::SpectrumAssignmentAlgorithm> WA_Alg =
        SA::SpectrumAssignmentAlgorithm::create_SpectrumAssignmentAlgorithm(
            SA::SpectrumAssignmentAlgorithm::FFE, T);
    std::shared_ptr<RA::RegeneratorAssignmentAlgorithm> RA_Alg =
        RA::RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
            RegAssignment_Algorithm, T);
    std::shared_ptr<RoutingWavelengthAssignment> RMSA =
        std::make_shared<RoutingWavelengthAssignment>
        (R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, T);

    std::shared_ptr<RP::RegeneratorPlacementAlgorithm> RP_Alg =
        RP::RegeneratorPlacementAlgorithm::create_RegeneratorPlacementAlgorithm(
            RegPlacement_Algorithm, T, RMSA, OptimizationLoad, NumCalls);

    RP_Alg->placeRegenerators();
}
