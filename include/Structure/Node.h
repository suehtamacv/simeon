#ifndef NODE_H
#define NODE_H

#include <boost/bimap.hpp>
#include <memory>
#include <vector>
#include <iostream>
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
    X(BroadcastAndSelect, "Broadcast and Switch", "bs") \
    X(SwitchingSelect, "Switching Select", "ss") //X Macros

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
#define X(a,b,c) a,
    enum NodeArchitecture {
        NODEARCH
    };
#undef X
    typedef boost::bimap<NodeArchitecture, std::string> NodeArchNicknameBimap;
    static NodeArchNicknameBimap NodeArchitecturesNicknames;
    typedef boost::bimap<NodeArchitecture, std::string> NodeArchNameBimap;
    static NodeArchNameBimap NodeArchitecturesNames;

    Node(int ID, NodeType T = TransparentNode,
         NodeArchitecture A = Default_Arch);
    Node(const Node &node);

    bool operator==(const Node &) const;
    bool operator<(const Node &) const;

    const int ID;
    std::vector<std::weak_ptr<Node>> Neighbours;
    std::vector<std::shared_ptr<Link>> Links;
    std::vector<std::shared_ptr<Device>> Devices;

    NodeArchitecture get_NodeArch();
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

    static void load() {}
  private:
    NodeType Type;
    NodeArchitecture Architecture;
    void create_Devices();
    unsigned int NumRegenerators;
    unsigned int NumUsedRegenerators;
    unsigned long long TotalNumRequestedRegenerators;
    unsigned int MaxSimultUsedRegenerators;
    static NodeArchitecture Default_Arch;
};

#endif // NODE_H
