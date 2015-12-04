#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <memory>
#include <vector>
#include <Structure/Node.h>


class Topology {
  public:
    Topology();
    unsigned int numNodes;
    std::vector<std::shared_ptr<Node>> Nodes;
};

#endif // TOPOLOGY_H
