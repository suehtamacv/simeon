#include <SimulationTypes/SimulationType.h>
#include "SimulationTypes.h"
#include <boost/assign.hpp>
#include <gtest/gtest.h>
#include <boost/program_options.hpp>
#include <iostream>
#include <GeneralClasses/SpectralDensity.h>

using namespace Simulations;

SimulationType::Network_Type SimulationType::Type;
std::vector<SimulationType::Physical_Impairment> SimulationType::Metrics;

SimulationType::NetworkTypeBimap SimulationType::NetworkTypes =
    boost::assign::list_of<SimulationType::NetworkTypeBimap::relation>
#define X(a,b,c) (a,b)
    NETWORK_TYPE
#undef X
    ;

SimulationType::NetworkTypeNicknameBimap SimulationType::NetworkTypesNicknames =
    boost::assign::list_of<SimulationType::NetworkTypeNicknameBimap::relation>
#define X(a,b,c) (a,c)
    NETWORK_TYPE
#undef X
#undef NETWORK_TYPE
    ;

SimulationType::SimulationTypeNameBimap SimulationType::SimulationTypeNames =
    boost::assign::list_of<SimulationType::SimulationTypeNameBimap::relation>
#define X(a,b,c,d) (a,b)
    SIMULATION_TYPE
#undef X
    ;

SimulationType::SimulationTypeNicknameBimap
SimulationType::SimulationTypeNicknames =
    boost::assign::list_of<SimulationType::SimulationTypeNicknameBimap::relation>
#define X(a,b,c,d) (a,c)
    SIMULATION_TYPE
#undef X
    ;

SimulationType::MetricTypeBimap SimulationType::MetricTypes =
    boost::assign::list_of<SimulationType::MetricTypeBimap::relation>
#define X(a,b,c) (a,b)
    PHYSICAL_IMPAIRMENTS
#undef X
    ;

SimulationType::MetricTypeNicknameBimap SimulationType::MetricTypesNicknames =
    boost::assign::list_of<SimulationType::MetricTypeNicknameBimap::relation>
#define X(a,b,c) (a,c)
    PHYSICAL_IMPAIRMENTS
#undef X
#undef PHYSICAL_IMPAIRMENTS
    ;

SimulationType::SimulationType(Simulation_Type SimType) : SimType(SimType)
{

}

void SimulationType::load()
{
    std::cout << std::endl << "-> Select a physical impairment. (-1 to exit)"
              << std::endl;
    do
        {
        std::vector<SimulationType::Physical_Impairment> chosenMetrics;

        do
            {
            unsigned int numPossibleMetrics = 0;

            for (auto &metric : SimulationType::MetricTypes.left)
                {
                if (std::find(chosenMetrics.begin(), chosenMetrics.end(),
                              metric.first) != chosenMetrics.end())
                    {
                    continue;
                    } //Verifies whether the metric has already been chosen.

                std::cout << "(" << metric.first << ")\t" << metric.second << std::endl;
                numPossibleMetrics++;
                }

            if(numPossibleMetrics == 0)
                {
                break;
                }

            int Metric;
            std::cin >> Metric;

            if (std::cin.fail() ||
                    !SimulationType::MetricTypes.left.count((SimulationType::Physical_Impairment)
                            Metric))
                {
                std::cin.clear();
                std::cin.ignore();

                if(Metric == -1)
                    {
                    break;
                    }

                std::cerr << "Invalid impairment." << std::endl;
                }
            else if (std::find(chosenMetrics.begin(), chosenMetrics.end(),
                               (SimulationType::Physical_Impairment) Metric) == chosenMetrics.end())
                {
                chosenMetrics.push_back((SimulationType::Physical_Impairment) Metric);
                } //Verifies that the metric hasn't been chosen.

            std::cout << std::endl << "-> Select a physical impairment. (-1 to exit)"
                      << std::endl;
            }
        while(1);

        for(unsigned int i = 0; i < chosenMetrics.size(); i++)
            {
            if(chosenMetrics.at(i) == SimulationType::Physical_Impairment::asenoise)
                {
                considerAseNoise = true;
                Metrics.push_back(SimulationType::Physical_Impairment::asenoise);
                }

            if(chosenMetrics.at(i) ==
                    SimulationType::Physical_Impairment::filterimperfection)
                {
                considerFilterImperfection = true;
                SpectralDensity::define_SignalsFilterOrder();
                Metrics.push_back(SimulationType::Physical_Impairment::filterimperfection);
                }
            }
        }
    while(0); //Dummy do-while. Only to encapsulate reading.

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

    EXPECT_TRUE(SimConfigFile.is_open()) << "Output file is not open";

    SimConfigFile << "  [general]" << std::endl << std::endl;
    SimConfigFile << "  SimulationType = " << SimulationTypeNicknames.left.at(
                      SimType) << std::endl;
    SimConfigFile << "  Metrics =";
    for(auto &metric : Metrics)
        {
        SimConfigFile << " " << SimulationType::MetricTypesNicknames.left.at(metric);
        }
    SimConfigFile << std::endl;

    if(considerFilterImperfection)
        {
        SimConfigFile << "  TxFilterOrder = " << SpectralDensity::TxFilterOrder <<
                      std::endl;
        SimConfigFile << "  GaussianFilterOrder = " << SpectralDensity::GaussianOrder <<
                      std::endl;
        }

}

std::shared_ptr<SimulationType> SimulationType::create()
{
    return start();
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
#define X(a,b,c,d) case a: simulation = std::make_shared<d>(); break;
                    SIMULATION_TYPE
#undef X
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
    ConfigFileName =
        "SimConfigFile.ini"; // File with previous simulation configurations

    using namespace boost::program_options;

    options_description ConfigDesctription("Configurations Data");
    ConfigDesctription.add_options()("general.SimulationType",
                                     value<std::string>()->required(), "Simulation Type")
    ("general.Metrics", value<std::vector<std::string>>()->multitoken(), "Metrics")
    ("general.TxFilterOrder", value<int>(), "Tx Filter Order")
    ("general.GaussianFilterOrder", value<int>(), "Gaussian Filter Order");;

    variables_map VariablesMap;
    std::ifstream ConfigFile(ConfigFileName, std::ifstream::in);
    EXPECT_TRUE(ConfigFile.is_open()) << "Input file is not open";
    store(parse_config_file<char>(ConfigFile, ConfigDesctription, true),
          VariablesMap);
    ConfigFile.close();
    notify(VariablesMap);

    std::string SimType = VariablesMap["general.SimulationType"].as<std::string>();
    Simulation_Type Sim_Type = SimulationTypeNicknames.right.at(SimType);

    std::shared_ptr<SimulationType> simulation;
    switch (Sim_Type)
        {
#define X(a,b,c,d) case a: simulation = std::make_shared<d>(); break;
            SIMULATION_TYPE
#undef X
        }

    std::vector<std::string> MetricsList =
        VariablesMap.find("general.Metrics")->second.as<std::vector<std::string>>();

    for(auto &metric : MetricsList)
        {
        std::stringstream SimMetrics(metric);
        std::string Aux;
        while(!SimMetrics.eof())
            {
            SimMetrics >> Aux;
            Metrics.push_back((SimulationType::Physical_Impairment)
                              SimulationType::MetricTypesNicknames.right.at(Aux));

            if(SimulationType::MetricTypesNicknames.right.at(Aux) ==
                    SimulationType::Physical_Impairment::filterimperfection)
                {
                considerFilterImperfection = true;
                SpectralDensity::TxFilterOrder =
                    VariablesMap["general.TxFilterOrder"].as<int>();
                SpectralDensity::GaussianOrder =
                    VariablesMap["general.GaussianFilterOrder"].as<int>();
                }
            if(SimulationType::MetricTypesNicknames.right.at(Aux) ==
                    SimulationType::Physical_Impairment::asenoise)
                {
                considerAseNoise = true;
                }
            }
        }

    simulation->load_file(ConfigFileName);

    return simulation;
}
