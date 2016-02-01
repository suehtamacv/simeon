#ifndef SIMULATIONTYPE_H
#define SIMULATIONTYPE_H

#include <fstream>
#include <string>
#include <boost/bimap.hpp>
#include <Structure/Topology.h>

namespace Simulations
{

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

#define X(a,b,c) a,
    enum Network_Type
    {
        NETWORK_TYPE
    };
#undef X

#define X(a,b,c,d) a,
    enum Simulation_Type
    {
        SIMULATION_TYPE
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

    virtual void run() = 0;
    virtual void load() = 0;
    virtual void print() = 0;
    virtual void save(std::string) = 0;
    virtual void load_file(std::string) = 0;
    virtual void help() = 0;

    static Network_Type Type;
    Topology::DefaultTopologies Chosen_Topology;
    std::shared_ptr<Topology> T;
};

}

#endif // SIMULATIONTYPE_H
