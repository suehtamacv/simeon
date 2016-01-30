#include <SimulationTypes/Simulation_PSROptimization.h>
#include <GeneralPurposeAlgorithms/PSO.h>
#include <iomanip>
#include <RWA/RoutingAlgorithms/PowerSeriesRouting/Costs.h>
#include <SimulationTypes/NetworkSimulation.h>
#include <Calls.h>
#include <RWA.h>
#include <Structure/Link.h>

double Simulation_PSROptimization::NumCalls;
double Simulation_PSROptimization::OptimizationLoad;
std::vector<std::shared_ptr<PSR::Cost>> Simulation_PSROptimization::Costs;
std::shared_ptr<Topology> Simulation_PSROptimization::Fitness::T;
WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithms
Simulation_PSROptimization::WavAssign_Algorithm;
RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms
Simulation_PSROptimization::RegPlacement_Algorithm;
RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms
Simulation_PSROptimization::RegAssignment_Algorithm;

Simulation_PSROptimization::Simulation_PSROptimization() :
    SimulationType(Simulation_Type::psroptimization)
{
    hasLoaded = hasRun = false;
}

void Simulation_PSROptimization::help()
{
    std::cout << "\t\tPSR OPTIMIZATION SIMULATION" << std::endl << std::endl <<
              "This simulation runs the Particle Swarm Optimization algorithm"
              " to find a set of coefficients that minimize the call blocking"
              " probability of the network. Warning: this usually takes"
              " some time." << std::endl;
}

void Simulation_PSROptimization::load()
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

    std::cout << std::endl << "-> Define the minimum PSR Exponent." << std::endl;

    do
        {
        int nmin;
        std::cin >> nmin;

        if (std::cin.fail())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid minimum exponent." << std::endl;
            std::cout << std::endl << "-> Define the minimum PSR Exponent."
                      << std::endl;
            }
        else
            {
            NMin = nmin;
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the maximum PSR Exponent." << std::endl;

    do
        {
        int nmax;
        std::cin >> nmax;

        if (std::cin.fail() || nmax < NMin)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid maximum exponent." << std::endl;
            std::cout << std::endl << "-> Define the maximum PSR Exponent." << std::endl;
            }
        else
            {
            NMax = nmax;
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Choose the PSR Costs." << std::endl;

    do
        {
        std::vector<PSR::Cost::PossibleCosts> chosenCosts;

        do
            {
            int numPossibleCosts = 0;

            for (auto &cost : PSR::Cost::CostsNames.left)
                {
                if (std::find(chosenCosts.begin(), chosenCosts.end(),
                              cost.first) != chosenCosts.end())
                    {
                    continue;
                    } //Verifies whether the cost has already been chosen.

                std::cout << "(" << cost.first << ")\t" << cost.second << std::endl;
                numPossibleCosts++;
                }

            if (numPossibleCosts == 0)
                {
                break;
                }

            int Cost;
            std::cin >> Cost;

            if (std::cin.fail() ||
                    PSR::Cost::CostsNames.left.count((PSR::Cost::PossibleCosts) Cost) == 0)
                {
                std::cin.clear();
                std::cin.ignore();

                if (Cost == -1 && !chosenCosts.empty())
                    {
                    break;
                    }

                std::cerr << "Invalid Cost." << std::endl;
                }
            else if (std::find(chosenCosts.begin(), chosenCosts.end(),
                               (PSR::Cost::PossibleCosts) Cost) == chosenCosts.end())
                {
                chosenCosts.push_back((PSR::Cost::PossibleCosts) Cost);
                Costs.push_back(PSR::Cost::createCost(
                                    (PSR::Cost::PossibleCosts) Cost, NMin, NMax, T));
                } //Verifies that the cost hasn't been chosen.

            std::cout << std::endl << "-> Choose the PSR Costs. (-1 to exit)" << std::endl;
            }
        while (1);

        }
    while (0);   //Dummy do-while. Only to encapsulate reading.

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
        std::cin >> FileName;

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

    hasLoaded = true;
}

void Simulation_PSROptimization::create_Simulation()
{

}

void Simulation_PSROptimization::save(std::string)
{
    // save parameters in file
}

void Simulation_PSROptimization::load_file(std::string)
{
    // load parameters from a file
}

void Simulation_PSROptimization::print()
{
}

void Simulation_PSROptimization::run()
{
    if (!hasLoaded)
        {
        load();
        }

    if (!hasRun)
        {
        Fitness::T = T;
        int N = std::pow(NMax - NMin + 1, Costs.size());

        PSO_Optim =
            std::shared_ptr<PSO::ParticleSwarmOptimization<double, Fitness, Compare>>
            (new PSO::ParticleSwarmOptimization<double, Fitness, Compare>
             (P, G, N, XMin, XMax, VMin, VMax));
        }

    std::cout << std::endl << "* * RESULTS * *" << std::endl;

    for (unsigned i = 1; i <= G; i++)
        {
        if (!hasRun)
            {
            PSO_Optim->run_generation();
            }

        std::cout << "GENERATION\tCALL BLOCKING PROBABILITY" << std::endl;
        std::cout << i << "\t\t" << PSO_Optim->BestParticle->bestFit << std::endl;
        printCoefficients(FileName);
        }

    hasRun = true;
}

double Simulation_PSROptimization::Fitness::operator()(
    std::shared_ptr<PSO::PSO_Particle<double>> particle)
{

    //Creates a copy of the topology.
    auto TopologyCopy = std::make_shared<Topology>(*T);

    //Creates the RWA Algorithms
    auto R_Alg = std::make_shared<PowerSeriesRouting>(TopologyCopy,
                 Simulation_PSROptimization::Costs);
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg =
        WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
            Simulation_PSROptimization::WavAssign_Algorithm, TopologyCopy);
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg;

    if (Simulation_PSROptimization::Type == TranslucentNetwork)
        {
        RA_Alg = RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
                     Simulation_PSROptimization::RegAssignment_Algorithm, TopologyCopy);
        }
    else
        {
        RA_Alg = nullptr;
        }

    //Initializes routing algorithm with the particle.
    R_Alg->initCoefficients(particle.get()->X);

    //Creates the Call Generator and the RWA Object
    auto Generator = std::make_shared<CallGenerator>(TopologyCopy,
                     Simulation_PSROptimization::OptimizationLoad,
                     TransmissionBitrate::DefaultBitrates);
    auto RWA = std::make_shared<RoutingWavelengthAssignment> (R_Alg, WA_Alg, RA_Alg,
               ModulationScheme::DefaultSchemes, TopologyCopy);

    return
        NetworkSimulation(Generator, RWA, Simulation_PSROptimization::NumCalls).
        get_CallBlockingProbability();
}

void Simulation_PSROptimization::printCoefficients(std::string file,
        bool override)
{
    std::ofstream OutFile;

    if (override)
        {
        OutFile.open(file);
        }
    else
        {
        OutFile.open(file, std::ofstream::out | std::ofstream::app);
        }

    OutFile << "  [PSR]" << std::endl << std::endl;

    OutFile << "minexponent = " << NMin << std::endl;

    OutFile << "maxexponent = " << NMax << std::endl;

    OutFile << "costs =";

        {
        for (auto &cost : Costs)
            {
            OutFile << " " << PSR::Cost::CostsNicknames.left.at(cost->Type);
            }

        OutFile << std::endl;
        }

    OutFile << "bestfit = " << PSO_Optim->BestParticle->bestFit << std::endl;

    OutFile << "coefficients =";

        {
        for (auto &coef : PSO_Optim->BestParticle->P)
            {
            OutFile << " " << std::setprecision(15) << coef;
            }

        OutFile << std::endl;
        }

}
