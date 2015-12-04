#include <Structure/Topology.h>
#include <boost/assert.hpp>
#include <boost/program_options.hpp>
#include <fstream>
#include <Structure/Link.h>

Topology::Topology(std::string TopologyFileName) {
    std::ifstream TopologyFile;
    TopologyFile.open(TopologyFileName);
    BOOST_ASSERT_MSG(TopologyFile.is_open(), "Topology file could not be open.");
}

std::weak_ptr<Node> Topology::add_Node(Node::Node_Type Type,
                                       Node::Node_Architecure Arch, int NumReg) {
    Nodes.push_back(std::shared_ptr<Node>(new Node(Nodes.size() + 1,
                                          Type, Arch, NumReg)));
    return (std::weak_ptr<Node>) Nodes.back();
}

std::weak_ptr<Link> Topology::add_Link(std::weak_ptr<Node> Origin,
                                       std::weak_ptr<Node> Destination, long double Length) {
    Links.push_back(std::shared_ptr<Link>(new Link(Origin, Destination, Length)));
    Origin.lock()->insert_Link(Destination.lock().get(), Links.back());
    return (std::weak_ptr<Link>) Links.back();
}
