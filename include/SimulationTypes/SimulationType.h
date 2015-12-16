#ifndef SIMULATIONTYPE_H
#define SIMULATIONTYPE_H

#include <fstream>
#include <string>
#include <boost/bimap.hpp>
#include <Structure/Topology.h>

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
    virtual void save(std::ofstream) = 0;
    virtual void load_file(std::ifstream) = 0;
    virtual void help() = 0;

    NetworkType Type;
    Topology T;
};

#endif // SIMULATIONTYPE_H
