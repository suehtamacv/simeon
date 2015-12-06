#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <Structure/Node.h>

typedef std::pair<unsigned, unsigned> OrigDestPair;

class Link;

class Topology {
  public:
    /**
    * @brief Topology is the basic constructor for a Topology.
    * @param TopologyFile is the file in which the Topology was stored.
    */
    Topology(std::string TopologyFileName);
    /**
     * @brief Topology is the constructor for a empty Topology.
     */
    Topology();

    std::vector<std::shared_ptr<Node>> Nodes;
    std::map<OrigDestPair, std::shared_ptr<Link>> Links;

    std::weak_ptr<Node> add_Node(int NodeID = -1,
                                 Node::Node_Type = Node::TransparentNode,
                                 Node::Node_Architecure = Node::SwitchingSelect, int NumReg = 0);
    std::weak_ptr<Link> add_Link(std::weak_ptr<Node> Origin,
                                 std::weak_ptr<Node> Destination, long double Length);

    void read_Topology(std::string TopologyFileName);
    void print_Topology(std::string TopologyFileName);
};

#endif // TOPOLOGY_H
