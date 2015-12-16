#ifndef NODE_H
#define NODE_H

#include <boost/bimap.hpp>
#include <memory>
#include <vector>
#include <GeneralClasses/Signal.h>
#include <Devices/Device.h>

class Link;

class Node {
  public:
#define NODETYPE \
    X(TransparentNode, "transparent") \
    X(TranslucentNode, "translucent") \
    X(OpaqueNode, "opaque") //X Macros

#define NODEARCH \
    X(BroadcastAndSelect, "bs") \
    X(SwitchingSelect, "ss") //X Macros

    /**
    * @brief The NodeType enum is used to set the type of node.
    *
    * Use TransparentNode if the node is transparent, with no regenerators, TranslucentNode if the node is
    * translucent, with a limited amount of regenerators, or OpaqueNode if the node is opaque, that is,
    * has a infinity amount of regenerators.
    */
#define X(a,b) a,
    enum NodeType {
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
#define X(a,b) a,
    enum NodeArchitecure {
        NODEARCH
    };
#undef X
    typedef boost::bimap<NodeArchitecure, std::string> NodeArchBimap;
    static NodeArchBimap NodeArchitectures;

    Node(int ID, NodeType T = TransparentNode,
         NodeArchitecure A = SwitchingSelect);
    Node(const Node &node);

    bool operator==(const Node &) const;
    bool operator<(const Node &) const;

    const int ID;
    std::vector<std::weak_ptr<Node>> Neighbours;
    std::vector<std::shared_ptr<Link>> Links;
    std::vector<std::shared_ptr<Device>> Devices;

    NodeArchitecure get_NodeArch();
    NodeType get_NodeType();
    unsigned int get_NumRegenerators();
    unsigned int get_NumAvailableRegenerators();
    unsigned long long get_TotalNumRequestedRegenerators();
    unsigned int get_NumMaxSimultUsedRegenerators();

    void request_Regenerators(unsigned int);
    void free_Regenerators(unsigned int);

    void insert_Link(std::weak_ptr<Node> N, std::shared_ptr<Link> Link);

    Signal &bypass(Signal &);
    Signal &add(Signal &);
    Signal &drop(Signal &);

    void set_NumRegenerators(unsigned int);
    void set_NodeType(NodeType);
    bool hasAsNeighbour(std::weak_ptr<Node>);
  private:
    NodeType Type;
    NodeArchitecure Architecture;
    void create_Devices();
    unsigned int NumRegenerators;
    unsigned int NumUsedRegenerators;
    unsigned long long TotalNumRequestedRegenerators;
    unsigned int MaxSimultUsedRegenerators;
};

#endif // NODE_H
