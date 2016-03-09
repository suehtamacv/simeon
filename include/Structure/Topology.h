#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <boost/bimap.hpp>
#include <Structure/Node.h>

class Link;

class Topology
{
public:
#define DEFAULT_TOPOLOGIES \
    X(European, "European", "data/topologies/European") \
    X(German, "German", "data/topologies/German") \
    X(NSFNet, "NSFNet", "data/topologies/NSFNet") \
    X(PacificBell, "Pacific Bell", "data/topologies/PacificBell") \
    X(Top1, "Topology 1", "data/topologies/Top1") \
    X(USBackbone, "US Backbone", "data/topologies/USBackbone")\
    X(P2P4, "Point-to-Point with 4 nodes", "data/topologies/P2P4") //Code Name, Official Name, FilePath

#define X(a,b,c) a,
    enum DefaultTopologies
    {
        DEFAULT_TOPOLOGIES
    };
#undef X

    typedef boost::bimap<DefaultTopologies, std::string> DefaultTopNamesBimap;
    static DefaultTopNamesBimap DefaultTopologiesNames;
    typedef boost::bimap<DefaultTopologies, std::string> DefaultTopPathsBimap;
    static DefaultTopPathsBimap DefaultTopologiesPaths;

    /**
     * @brief Topology is the constructor for a empty Topology.
     */
    Topology();
    /**
     * @brief Topology is the copy constructor for a Topology.
     */
    Topology(const Topology &topology);
    /**
    * @brief Topology is the basic constructor for a Topology.
    * @param TopologyFileName is the file in which the Topology was stored.
    */
    Topology(std::string TopologyFileName);


    std::vector<std::shared_ptr<Node>> Nodes;
    std::map<std::pair<int, int>, std::shared_ptr<Link>> Links;

    std::weak_ptr<Node> add_Node(int NodeID = -1,
                                 Node::NodeType = Node::TransparentNode,
                                 Node::NodeArchitecture = Node::SwitchingSelect, int NumReg = 0);
    std::weak_ptr<Link> add_Link(std::weak_ptr<Node> Origin,
                                 std::weak_ptr<Node> Destination, double Length);

    static std::shared_ptr<Topology> create_DefaultTopology(DefaultTopologies);

    void save(std::string TopologyFileName);

    double get_LengthLongestLink();
    void set_avgSpanLength(double avgSpanLength);

    unsigned long get_NumRegenerators();

    double get_CapEx();
    double get_OpEx();

    double AvgSpanLength;
private:
    double LongestLink;
};

#endif // TOPOLOGY_H
