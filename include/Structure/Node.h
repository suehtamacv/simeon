#ifndef NODE_H
#define NODE_H

#include <boost/bimap.hpp>
#include <GeneralClasses/Signal.h>
#include <memory>
#include <vector>
#include <iostream>

class Link;
namespace Devices
{
class Device;
}

/**
 * @brief The Node class represents a node on the topology.
 */
class Node
{
public:
#define NODETYPE \
    X(TransparentNode, "transparent") \
    X(TranslucentNode, "translucent") \
    X(OpaqueNode, "opaque") //X Macros

#define NODEARCH \
    X(BroadcastAndSelect, "Broadcast and Switch", "bs") \
    X(SwitchingSelect, "Switching Select", "ss") //X Macros

    /**
    * @brief The NodeType enum is used to set the type of node.
    *
    * Use TransparentNode if the node is transparent, with no regenerators,
    * TranslucentNode if the node is translucent, with a limited amount of
    * regenerators, or OpaqueNode if the node is opaque, i.e., has a infinite
    * amount of regenerators.
    */
#define X(a,b) a,
    enum NodeType
    {
        NODETYPE
    };
#undef X
    typedef boost::bimap<NodeType, std::string> NodeTypeBimap;
    static NodeTypeBimap NodeTypes;

    /**
     * @brief The Node_Architecure enum is used to set the type of node.
     *
     * There are two architectures, Broadcast And Select, that uses splitters
     * and SSS, and Switching Select, that only uses SSS devices.
     */
#define X(a,b,c) a,
    enum NodeArchitecture
    {
        NODEARCH
    };
#undef X
    typedef boost::bimap<NodeArchitecture, std::string> NodeArchNicknameBimap;
    static NodeArchNicknameBimap NodeArchitecturesNicknames;
    typedef boost::bimap<NodeArchitecture, std::string> NodeArchNameBimap;
    static NodeArchNameBimap NodeArchitecturesNames;

    /**
     * @brief Node is the standard constructor for a node.
     * @param ID is the number that identifies this node.
     * @param T is the type of node (TranslucentNode or TransparentNode)
     * @param A is the node Architecture (BS or SS)
     */
    Node(int ID, NodeType T = TransparentNode, NodeArchitecture A = Default_Arch);
    Node(const Node &node);

    bool operator==(const Node &) const;
    bool operator<(const Node &) const;

    /**
     * @brief ID is the unique identifier of this node on the topology.
     */
    const int ID;
    /**
     * @brief Neighbours is a vector containing the nodes that are neighbours to
     * this node.
     */
    std::vector<std::weak_ptr<Node>> Neighbours;
    /**
     * @brief isNeighbourOf is a vector containing the nodes which this node is
     * a neighbour of.
     */
    std::vector<std::weak_ptr<Node>> isNeighbourOf;
    /**
     * @brief Links is a vector containing the links whose origin node is this
     * node.
     */
    std::vector<std::shared_ptr<Link>> Links;

    std::vector<std::shared_ptr<Link>> incomingLinks;
    /**
     * @brief Devices is a vector containing the optical devices that comprise
     * this node.
     */
    std::vector<std::shared_ptr<Devices::Device>> Devices;
    /**
     * @brief Regenerators is a vector containing only the electronic regenerators
     * available on this node.
     */
    std::vector<std::shared_ptr<Devices::Device>> Regenerators;

    /**
     * @brief get_NodeArch returns the architecture of this node.
     * @return the architecture of this node.
     */
    NodeArchitecture get_NodeArch();
    /**
     * @brief get_NodeType returns the type of this node.
     * @return the type of this node.
     */
    NodeType get_NodeType();
    /**
     * @brief get_NumRegenerators returns the quantity of electronic regenerators
     * installed on this node.
     * @return the quantity of electronic regenerators installed on this node.
     */
    unsigned int get_NumRegenerators();
    /**
     * @brief get_NumAvailableRegenerators returns the quantity of available
     * electronic regenerators.
     * @return the quantity of available electronic regenerators.
     */
    unsigned int get_NumAvailableRegenerators();
    /**
     * @brief get_TotalNumRequestedRegenerators returns the quantity of regenerators
     * ever requested on this node.
     * @return the quantity of regenerators ever requested on this node.
     */
    unsigned long long get_TotalNumRequestedRegenerators();
    /**
     * @brief get_NumMaxSimultUsedRegenerators returns the maximum quantity of
     * regenerators that were ever simultaneuosly used on this node.
     * @return the maximum quantity of regenerators that were ever simultaneuosly
     * used on this node.
     */
    unsigned int get_NumMaxSimultUsedRegenerators();

    /**
     * @brief request_Regenerators occupies i regenerators on this node,
     * if available.
     */
    void request_Regenerators(unsigned int);
    /**
     * @brief free_Regenerators frees i regenerators on this node, if occupied.
     */
    void free_Regenerators(unsigned int);

    /**
     * @brief insert_Link creates a reference to the Link departing to this node
     * and going to Node N.
     * @param N is the destination node.
     * @param Link is the link going from this node to N.
     */
    void insert_Link(std::weak_ptr<Node> N, std::shared_ptr<Link> Link);

    /**
     * @brief bypass bypasses a signal by all the optical devices of this node.
     * Observe that the parameter Signal is modified through the bypassing.
     * @return the Signal after it bypassed all the optical devices of this node.
     */
    Signal &bypass(Signal &);
    /**
     * @brief add bypasses a signal by the exit optical devices of this node,
     * effectively inserting a connection from this node. Observe that the parameter
     * Signal is modified through the bypassing.
     * @return the Signal after it bypassed the required optical devices of this node.
     */
    Signal &add(Signal &);
    /**
     * @brief drop bypasses a signal by the entrance optical devices of this node,
     * effectively removing a connection from this node. Observe that the parameter
     * Signal is modified through the bypassing.
     * @return the Signal after it bypassed the required optical devices of this node.
     */
    Signal &drop(Signal &);

    /**
     * @brief set_NumRegenerators sets i electronic regenerators on this node.
     * @param i is the new number of regenerators in this node.
     */
    void set_NumRegenerators(unsigned int i);
    /**
     * @brief set_NodeType sets the type of this node. Only Transparent nodes
     * can receive electronic regenerators.
     */
    void set_NodeType(NodeType);
    /**
     * @brief hasAsNeighbour returns true iff is this node has node N as neighbour.
     * @return true iff is this node has node N as neighbour.
     */
    bool hasAsNeighbour(std::weak_ptr<Node>);

    /**
     * @brief get_CapEx returns the CapEx of this node.
     * @return the CapEx of this node.
     */
    double get_CapEx();
    /**
     * @brief get_OpEx returns the OpEx of this node.
     * @return the OpEx of this node.
     */
    double get_OpEx();

    /**
     * @brief load loads the parameters required to create the nodes of the
     * topology.
     */
    static void load() {}

    friend std::ostream& operator<<(std::ostream &out, const Node& node);

private:
    NodeType Type;
    NodeArchitecture Architecture;
    void create_Devices();
    unsigned int NumUsedRegenerators;
    unsigned long long TotalNumRequestedRegenerators;
    unsigned int MaxSimultUsedRegenerators;
    static NodeArchitecture Default_Arch;
};

#endif // NODE_H
