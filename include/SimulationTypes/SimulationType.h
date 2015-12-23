#ifndef SIMULATIONTYPE_H
#define SIMULATIONTYPE_H

#include <fstream>
#include <string>
#include <boost/bimap.hpp>
#include <Structure/Topology.h>

#include <RWA/RoutingAlgorithms/RoutingAlgorithm.h>
#include <RWA/WavelengthAssignmentAlgorithms/WavelengthAssignmentAlgorithm.h>
#include <RWA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>
#include <RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>

class SimulationType {
  public:

#define NETWORK_TYPE \
    X(TransparentNetwork, "Transparent Network") \
    X(TranslucentNetwork, "Translucent Network") //X Macros

#define X(a,b) a,
    enum NetworkType {
        NETWORK_TYPE
    };
#undef X

    typedef boost::bimap<NetworkType, std::string> NetworkTypeBimap;
    static NetworkTypeBimap NetworkTypes;

    SimulationType();

    virtual void run() = 0;
    virtual void load() = 0;
    virtual void print() = 0;
    virtual void save(std::string) = 0;
    virtual void load_file(std::string) = 0;
    virtual void help() = 0;

    static NetworkType Type;
    Topology::DefaultTopologies Chosen_Topology;
    std::shared_ptr<Topology> T;
};

#endif // SIMULATIONTYPE_H
