#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <memory>
#include <string>
#include <vector>
#include <Structure/Node.h>

class Link;

class Topology {
  public:
    /**
    * @brief Topology is the basic constructor for a Topology.
    * @param TopologyFile is the file in which the Topology was stored.
    */
    Topology(std::string TopologyFileName);

    unsigned int numNodes;
    std::vector<std::shared_ptr<Node>> Nodes;
    std::vector<std::shared_ptr<Link>> Links;

    std::weak_ptr<Node> add_Node(Node::Node_Type = Node::TransparentNode,
                                 Node::Node_Architecure = Node::SwitchingSelect, int NumReg = 0);
    std::weak_ptr<Link> add_Link(std::weak_ptr<Node> Origin,
                                 std::weak_ptr<Node> Destination, long double Length);
};

#endif // TOPOLOGY_H
