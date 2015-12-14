#include <RWA/RegeneratorPlacementAlgorithms/MostUsed.h>
#include <boost/assert.hpp>
#include <SimulationTypes/NetworkSimulation.h>

MostUsed::MostUsed(std::shared_ptr<Topology> T,
                   std::shared_ptr<NetworkSimulation> Optimization) :
    NX_RegeneratorPlacement(T),
    Optimization(Optimization) {

}

void MostUsed::placeRegenerators(unsigned N, unsigned X) {
    for (auto node : Optimization->Generator->T->Nodes) {
        node->set_NodeType(Node::OpaqueNode);
    }

    Optimization->run();
}
