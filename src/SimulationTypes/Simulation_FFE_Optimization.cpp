#include "include/SimulationTypes/Simulation_FFE_Optimization.h"
#include "Structure.h"

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

void Simulation_FFE_Optimization::save(std::string)
{

}

void Simulation_FFE_Optimization::load_file(std::string)
{

}

void Simulation_FFE_Optimization::print()
{

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
