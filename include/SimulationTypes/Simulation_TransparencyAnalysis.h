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

class Simulation_TransparencyAnalysis : public SimulationType
{
public:
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

    std::shared_ptr<Node> Orig_Origin, Orig_Destination;
    void find_OriginDestination();

    std::vector<InLineDistance_OSNR_Point> TransparentPoints;
    std::vector<InLineDistance_OSNR_Point> OpaquePoints;

    std::shared_ptr<ModulationScheme> minModulationScheme;
    std::shared_ptr<TransmissionBitrate> maxBitrate;
};

}
#endif // SIMULATION_TRANSPARENCYANALYSIS_H
