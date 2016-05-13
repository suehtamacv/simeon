#ifndef SIMULATION_TRANSPARENCYANALYSIS_H
#define SIMULATION_TRANSPARENCYANALYSIS_H

#include "SimulationType.h"
#include <vector>
#include <memory>
#include <GeneralClasses/ModulationScheme.h>
#include <GeneralClasses/TransmissionBitrate.h>

class Node;

namespace Simulations
{

/**
 * @brief The Simulation_TransparencyAnalysis class represents a transparency
 * analysis simulation.
 *
 * This simulation varies the average distance between inline amplifiers and the
 * input OSNR, and checks whether it's still possible to establish a connection
 * in the route with longest length found by the Shortest Path routing algorithm,
 * using the greatest possible bitrate and any modulation scheme. If it's possible
 * to establish such connection, then the network is said to be "transparent".
 */
class Simulation_TransparencyAnalysis : public SimulationType
{
public:
    /**
     * @brief Simulation_TransparencyAnalysis is the standard constructor.
     */
    Simulation_TransparencyAnalysis();

    void help();
    void run();
    void load();
    void save(std::string);
    void load_file(std::string);
    void print();

private:
    typedef std::pair<double, double> InLineDistance_OSNR_Point;

    bool hasLoaded;
    bool hasRun;

    double minOSNR, maxOSNR, stepOSNR;
    double minAvgLinkSpan, maxAvgLinkSpan, stepAvgLinkSpan;
    std::string FileName;

    std::shared_ptr<Node> Orig_Origin, Orig_Destination;
    void find_OriginDestination();

    std::vector<InLineDistance_OSNR_Point> TransparentPoints;
    std::vector<InLineDistance_OSNR_Point> OpaquePoints;

    std::shared_ptr<ModulationScheme> minModulationScheme;
    std::shared_ptr<TransmissionBitrate> maxBitrate;
};

}
#endif // SIMULATION_TRANSPARENCYANALYSIS_H
