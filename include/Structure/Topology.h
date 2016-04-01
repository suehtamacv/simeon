#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <boost/bimap.hpp>
#include <Structure/Node.h>

class Link;

/**
 * @brief The Topology class represents a topology, i.e. a set of links and
 * nodes.
 */
class Topology
{
public:
#define DEFAULT_TOPOLOGIES \
    X(European, "European", "data/topologies/European") \
    X(German, "German", "data/topologies/German") \
    X(NSFNet, "NSFNet", "data/topologies/NSFNet") \
    X(PacificBell, "Pacific Bell", "data/topologies/PacificBell") \
    X(P2P4, "Point-to-Point with 4 nodes", "data/topologies/P2P4") \
    X(Top1, "Topology 1", "data/topologies/Top1") \
    X(Top2, "Topology 2", "data/topologies/Top2") \
    X(USBackbone, "US Backbone", "data/topologies/USBackbone") //Code Name, Official Name, FilePath

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

    /**
     * @brief Nodes is a vector containing pointers to the Nodes in this topology.
     */
    std::vector<std::shared_ptr<Node>> Nodes;
    /**
     * @brief Links is a map relating the origin destination pair (int a, int b)
     * and a possible pointer to a link from Node a to Node b.
     */
    std::map<std::pair<int, int>, std::shared_ptr<Link>> Links;

    /**
     * @brief add_Node is used to add a node to this topology.
     * @param NodeID is the ID of the new node.
     * @param NumReg is the number of electronic regenerators in this node.
     * @return is a pointer to the created node.
     */
    std::weak_ptr<Node> add_Node(int NodeID = -1,
                                 Node::NodeType = Node::TransparentNode,
                                 Node::NodeArchitecture = Node::SwitchingSelect, int NumReg = 0);
    /**
     * @brief add_Link is used to add a link to this topology.
     * @param Origin is a pointer to the Origin node.
     * @param Destination is a pointer to the Destination node.
     * @param Length is the length of this link.
     * @return a pointer to the created link.
     */
    std::weak_ptr<Link> add_Link(std::weak_ptr<Node> Origin,
                                 std::weak_ptr<Node> Destination, double Length);

    /**
     * @brief create_DefaultTopology is used to create a Topology equal to one of
     * the set of "default topologies", that come bundled with this simulator.
     * @return a pointer to such topology.
     */
    static std::shared_ptr<Topology> create_DefaultTopology(DefaultTopologies);

    /**
     * @brief save is used to save this topology data.
     * @param TopologyFileName is the filename where this topology will be saved.
     */
    void save(std::string TopologyFileName);

    /**
     * @brief get_LengthLongestLink returns the length of the longest link in this
     * topology.
     * @return the length of the longest link in this topology.
     */
    double get_LengthLongestLink();
    /**
     * @brief set_AvgSpanLength is used to set the average length between in line
     * amplifiers in all the links.
     * @param avgSpanLength is the new average length between in line amplifiers.
     */
    void set_avgSpanLength(double avgSpanLength);

    /**
     * @brief get_NumRegenerators returns the total number of regenerators in this
     * topology.
     * @return the total number of regenerators in this topology.
     */
    unsigned long get_NumRegenerators();
    /**
     * @brief get_NumTranslucentNodes returns the number of translucent nodes in
     * this topology.
     * @return the number of translucent nodes in this topology.
     */
    unsigned long get_NumTranslucentNodes();

    /**
     * @brief get_CapEx returns the CapEx of this topology.
     * @return the CapEx of this topology.
     */
    double get_CapEx();
    /**
     * @brief get_OpEx returns the OpEx of this topology.
     * @return the OpEx of this topology.
     */
    double get_OpEx();

    /**
     * @brief AvgSpanLength is the average distance between in line amplifiers to
     * all the links in this topology.
     */
    double AvgSpanLength;
private:
    double LongestLink;
};

#endif // TOPOLOGY_H
