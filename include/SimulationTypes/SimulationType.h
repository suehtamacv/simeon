#ifndef SIMULATIONTYPE_H
#define SIMULATIONTYPE_H

#include <fstream>
#include <string>
#include <boost/bimap.hpp>
#include <Structure/Topology.h>

namespace Simulations
{
/**
 * @brief The SimulationType class represents a simulation that can be run by
 * this simulator.
 */
class SimulationType
{
public:
#define NETWORK_TYPE \
    X(TransparentNetwork, "Transparent Network", "Transparent") \
    X(TranslucentNetwork, "Translucent Network", "Translucent") //X Macros

#define SIMULATION_TYPE \
    X(transparency, "Transparency Analysis", "transparency", Simulation_TransparencyAnalysis) \
    X(morp3o, "MORP-3O Regenerator Placement", "morp3o", Simulation_NSGA2_RegnPlac) \
    X(networkload, "Network Load Variation", "networkload", Simulation_NetworkLoad) \
    X(psroptimization, "Power Series Routing PSO Optimization", "psroptimization", Simulation_PSROptimization) \
    X(regnum, "Number of Regenerators", "regnum", Simulation_RegeneratorNumber) \
    X(statisticaltrend, "Statistical Trend Analysis", "statisticaltrend", Simulation_StatisticalTrend)

#define PHYSICAL_IMPAIRMENTS \
    X(asenoise, "ASE Noise", "asenoise") \
    X(filterimperfection, "Filter Imperfection", "filterimperfection")

#define X(a,b,c) a,
    enum Network_Type
    {
        NETWORK_TYPE
    };
#undef X

#define X(a,b,c,d) a,
    /**
     * @brief The Simulation_Type enum defines the type of simulation that is
     * being created.
     */
    enum Simulation_Type
    {
        SIMULATION_TYPE
    };
#undef X

#define X(a,b,c) a,
    /**
     * @brief The Physical_Impairment enum represents the physical impairments
     * that are being considered on this simulation.
     */
    enum Physical_Impairment
    {
        PHYSICAL_IMPAIRMENTS
    };
#undef X

    SimulationType(Simulation_Type SimType);

    Simulation_Type SimType;

    static std::shared_ptr<SimulationType> create();
    static std::shared_ptr<SimulationType> start();
    static std::shared_ptr<SimulationType> open();

    typedef boost::bimap<Network_Type, std::string> NetworkTypeBimap;
    static NetworkTypeBimap NetworkTypes;
    typedef boost::bimap<Network_Type, std::string> NetworkTypeNicknameBimap;
    static NetworkTypeNicknameBimap NetworkTypesNicknames;
    typedef boost::bimap<Simulation_Type, std::string> SimulationTypeNameBimap;
    static SimulationTypeNameBimap SimulationTypeNames;
    typedef boost::bimap<Simulation_Type, std::string> SimulationTypeNicknameBimap;
    static SimulationTypeNameBimap SimulationTypeNicknames;
    typedef boost::bimap<Physical_Impairment, std::string> MetricTypeBimap;
    static MetricTypeBimap MetricTypes;
    typedef boost::bimap<Physical_Impairment, std::string> MetricTypeNicknameBimap;
    static MetricTypeNicknameBimap MetricTypesNicknames;

    static std::vector<SimulationType::Physical_Impairment> Metrics;

    /**
     * @brief run silently runs a simulation.
     */
    virtual void run() = 0;
    /**
     * @brief load loads the parameters required to the simulation.
     */
    virtual void load() = 0;
    /**
     * @brief print runs the simulation, and prints its results.
     */
    virtual void print() = 0;
    /**
     * @brief save saves the parameters of the simulation into a file.
     */
    virtual void save(std::string) = 0;
    /**
     * @brief load_file loads a file containing parameters to a simulation.
     */
    virtual void load_file(std::string) = 0;
    /**
     * @brief help prints a description of this simulation.
     */
    virtual void help() = 0;

    /**
     * @brief Type is the type of network being considered (e.g. Transparent or
     * Translucent)
     */
    static Network_Type Type;
    /**
     * @brief Chosen_Topology is the default topology chosen to run this simulation.
     */
    Topology::DefaultTopologies Chosen_Topology;
    /**
     * @brief T is a pointer to a "master" Topology.
     */
    std::shared_ptr<Topology> T;
};

}

#endif // SIMULATIONTYPE_H
