#include "SimulationTypes/Simulation_PowerRatioThreshold.h"
#include <Structure/Topology.h>
#include <Structure/Link.h>
#include <Structure/Node.h>
#include <Calls/CallGenerator.h>
#include <RMSA/RoutingWavelengthAssignment.h>
#include <iostream>
#include <boost/assert.hpp>
#include <boost/assign.hpp>
#include <boost/program_options.hpp>
#include <map>
#include <GeneralClasses/SpectralDensity.h>

using namespace RMSA;
using namespace Simulations;
using namespace ROUT;
using namespace SA;
using namespace RA;
using namespace RP;

Simulation_PowerRatioThreshold::Simulation_PowerRatioThreshold() :
    SimulationType(Simulation_Type::pratiothreshold)
{
    hasLoaded = false;

    Routing_Algorithm = (RoutingAlgorithm::RoutingAlgorithms) - 1;
    WavAssign_Algorithm =
        (SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithms) - 1;
    RegPlacement_Algorithm =
        (RegeneratorPlacementAlgorithm::RegeneratorPlacementAlgorithms) - 1;
    RegAssignment_Algorithm =
        (RegeneratorAssignmentAlgorithm::RegeneratorAssignmentAlgorithms) - 1;
}

void Simulation_PowerRatioThreshold::help()
{
    std::cout << "\t\tPOWER RATIO THRESHOLD VARIATION" << std::endl << std::endl <<
              "This simulation varies the power ratio threshold for the filter "
              "imperfection physical impairment, and analyzes the"
              " network performance in terms of call blocking probability." << std::endl;
}

void Simulation_PowerRatioThreshold::run()
{
    if(considerFilterImperfection)
    {
        if (!hasLoaded)
            {
            load();
            }

        std::cout << std::endl << "* * RESULTS * *" << std::endl;
        std::cout << "POWER RATIO THRESHOLD\tCALL BLOCKING PROBABILITY" << std::endl;

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
                std::cout << simulations[i]->RMSA->T->get_PowerRatioThreshold() << "\t\t"
                        << simulations[i]->get_CallBlockingProbability() << std::endl;
                OutFile << simulations[i]->RMSA->T->get_PowerRatioThreshold() << "\t\t"
                        << simulations[i]->get_CallBlockingProbability() << std::endl;
                }
            }
    }
}

void Simulation_PowerRatioThreshold::load()
{
    SimulationType::load();

    BOOST_ASSERT_MSG(considerFilterImperfection, "Filter Imperfection Impairment not selected.");

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
        Routing_Algorithm = RoutingAlgorithm::define_RoutingAlgorithm();

        //Wavelength Assignment Algorithm
        WavAssign_Algorithm =
            SA::SpectrumAssignmentAlgorithm::define_SpectrumAssignmentAlgorithm();

        if (Type == TranslucentNetwork)
            {
            //Regenerator Placement Algorithm
            RegPlacement_Algorithm =
                RegeneratorPlacementAlgorithm::define_RegeneratorPlacementAlgorithm();

            //Regenerator Assignment Algorithm
            RegAssignment_Algorithm =
                RegeneratorAssignmentAlgorithm::define_RegeneratorAssignmentAlgorithm();

            runLoadNX = true;
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
            std::cout << std::endl << "-> Define network load." << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the minimum power ratio threshold." << std::endl;

    do
        {
        std::cin >> MinPowerRatioThreshold;

        if (std::cin.fail() || MinPowerRatioThreshold < 0 || MinPowerRatioThreshold >= 1.0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid power ratio threshold." << std::endl;
            std::cout << std::endl << "-> Define the minimum power ratio threshold." << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the maximum power ratio threshold." << std::endl;

    do
        {
        std::cin >> MaxPowerRatioThreshold;

        if (std::cin.fail() || MaxPowerRatioThreshold < MinPowerRatioThreshold || MaxPowerRatioThreshold > 1.0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid power ratio threshold." << std::endl;
            std::cout << std::endl << "-> Define the maximum power ratio threshold." << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the power ratio threshold step." << std::endl;

    do
        {
        std::cin >> PowerRatioThresholdStep;

        if (std::cin.fail() || PowerRatioThresholdStep < 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid power ratio threshold." << std::endl;
            std::cout << std::endl << "-> Define the power ratio threshold step." << std::endl;
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
    runLoadNX = false;
}

void Simulation_PowerRatioThreshold::save(std::string SimConfigFileName)
{

}

void Simulation_PowerRatioThreshold::load_file(std::string ConfigFileName)
{

}

void Simulation_PowerRatioThreshold::print()
{
    if (!hasLoaded)
        {
        load();
        }

    std::cout << std::endl <<
              "  A Power Ratio Threshold Variation Simulation is about to start with the following parameters: "
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
              RoutingAlgorithm::RoutingAlgorithmNames.left.at(Routing_Algorithm)
              << std::endl;
    std::cout << "-> Wavelength Assignment Algorithm = " <<
              SpectrumAssignmentAlgorithm::SpectrumAssignmentAlgorithmNames.left.at(
                  WavAssign_Algorithm)
              << std::endl;
    if(Type == TranslucentNetwork)
        {
        std::cout << "-> Regenerator Placement Algorithm = " <<
                  RegeneratorPlacementAlgorithm::RegeneratorPlacementNames.left.at(
                      RegPlacement_Algorithm) << std::endl;
        std::cout << "-> Regenerator Assignment Algorithm = " <<
                  RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNames.left.at(
                      RegAssignment_Algorithm) << std::endl;
        }
    std::cout << "-> Number of Calls = " << NumCalls << std::endl;
    std::cout << "-> Network Load = " << NetworkLoad << std::endl;
    std::cout << "-> Maximum Power Ratio Threshold = " << MaxPowerRatioThreshold << std::endl;
    std::cout << "-> Minimum Power Ratio Threshold = " << MinPowerRatioThreshold << std::endl;
    std::cout << "-> Power Ratio Threshold Step = " << PowerRatioThresholdStep << std::endl;
}

void Simulation_PowerRatioThreshold::create_Simulations()
{
    if (Type == TranslucentNetwork)
        {
        place_Regenerators(T);
        }

    for (double prt = MinPowerRatioThreshold; prt <= MaxPowerRatioThreshold;
            prt += PowerRatioThresholdStep)
        {

        //Creates a copy of the topology.
        std::shared_ptr<Topology> TopologyCopy(new Topology(*T));
        TopologyCopy->set_PowerRatioThreshold(prt);

        //Creates the RMSA Algorithms
        std::shared_ptr<RoutingAlgorithm> R_Alg =
            RoutingAlgorithm::create_RoutingAlgorithm(Routing_Algorithm, TopologyCopy);
        std::shared_ptr<SA::SpectrumAssignmentAlgorithm> WA_Alg =
            SA::SpectrumAssignmentAlgorithm::create_SpectrumAssignmentAlgorithm(
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

        //Creates the Call Generator and the RMSA Object
        std::shared_ptr<CallGenerator> Generator(new CallGenerator(TopologyCopy, NetworkLoad));
        std::shared_ptr<RoutingWavelengthAssignment> RMSA(
            new RoutingWavelengthAssignment(
                R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, TopologyCopy));

        //Push simulation into stack
        simulations.push_back(
            std::shared_ptr<NetworkSimulation>(new NetworkSimulation(
                    Generator, RMSA, NumCalls)));

        }
}

void Simulation_PowerRatioThreshold::place_Regenerators(std::shared_ptr<Topology> T)
{
    std::shared_ptr<RoutingAlgorithm> R_Alg =
        RoutingAlgorithm::create_RoutingAlgorithm(
            Routing_Algorithm, T);
    std::shared_ptr<SA::SpectrumAssignmentAlgorithm> WA_Alg =
        SA::SpectrumAssignmentAlgorithm::create_SpectrumAssignmentAlgorithm(
            WavAssign_Algorithm, T);
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg =
        RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
            RegAssignment_Algorithm, T);
    std::shared_ptr<RoutingWavelengthAssignment> RMSA(
        new RoutingWavelengthAssignment(
            R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, T));

    std::shared_ptr<RegeneratorPlacementAlgorithm> RP_Alg =
        RegeneratorPlacementAlgorithm::create_RegeneratorPlacementAlgorithm(
            RegPlacement_Algorithm, T, RMSA, NetworkLoad, NumCalls, runLoadNX);

    RP_Alg->placeRegenerators();
}
