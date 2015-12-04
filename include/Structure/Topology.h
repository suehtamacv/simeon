#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <memory>
#include <string>
#include <vector>

class Node;

class Topology {
  public:
    /**
    * @brief Topology is the basic constructor for a Topology.
    * @param TopologyFile is the file in which the Topology was stored.
    */
    Topology(std::string TopologyFileName);

    unsigned int numNodes;
    std::vector<std::shared_ptr<Node>> Nodes;
};

#endif // TOPOLOGY_H
