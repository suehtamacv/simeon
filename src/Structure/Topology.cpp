#include <Structure/Topology.h>
#include <boost/assert.hpp>
#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Structure/Link.h>

Topology::Topology() {
    Nodes.clear();
    Links.clear();
}

Topology::Topology(std::string TopologyFileName) {
    std::ifstream TopologyFile;
    TopologyFile.open(TopologyFileName);
    BOOST_ASSERT_MSG(TopologyFile.is_open(), "Topology file could not be open.");
}

std::weak_ptr<Node> Topology::add_Node(int NodeID, Node::Node_Type Type,
                                       Node::Node_Architecure Arch, int NumReg) {

    if (NodeID == -1) {
        NodeID = Nodes.size() + 1;
    }

    Nodes.push_back(std::shared_ptr<Node>(new Node(NodeID, Type, Arch)));
    Nodes.back()->set_NumRegenerators(NumReg);
    return (std::weak_ptr<Node>) Nodes.back();
}

std::weak_ptr<Link> Topology::add_Link(std::weak_ptr<Node> Origin,
                                       std::weak_ptr<Node> Destination, long double Length) {
    Links.emplace(OrigDestPair(Origin.lock()->ID, Destination.lock()->ID),
                  std::shared_ptr<Link>(new Link(Origin, Destination, Length)));
    Origin.lock()->insert_Link(Destination, Links.at(OrigDestPair(Origin.lock()->ID,
                                                                  Destination.lock()->ID)));
    return (std::weak_ptr<Link>) Links.at(OrigDestPair(Origin.lock()->ID,
                                          Destination.lock()->ID));
}

void Topology::read_Topology(std::string TopologyFileName) {
    using namespace boost::program_options;

    Nodes.clear();
    Links.clear();

    options_description TopologyDescription("Topology");
    TopologyDescription.add_options()
    ("nodes.node", value<std::vector<std::string>>()->multitoken(),
     "Node Description")
    ("links.->", value<std::vector<std::string>>()->multitoken(),
     "Unidirectional Link Description");

    variables_map VariablesMap;

    store(parse_config_file<char>(TopologyFileName.c_str(), TopologyDescription),
          VariablesMap);

    //Reads nodes from configuration file.
    std::vector<std::string> NodesList =
        VariablesMap.find("nodes.node")->second.as<std::vector<std::string>>();

    for (auto node = NodesList.begin(); node != NodesList.end(); ++node) {
        int NodeId, Type, Arch, NumReg;

        std::istringstream NodeParameters(*node);
        NodeParameters >> NodeId >> Type >> Arch >> NumReg;

        add_Node(NodeId, (Node::Node_Type) Type, (Node::Node_Architecure) Arch, NumReg);
    }

    //Reads links from configuration file.
    std::vector<std::string> LinksList =
        VariablesMap.find("links.->")->second.as<std::vector<std::string>>();

    for (auto link = LinksList.begin(); link != LinksList.end(); ++link) {
        int OriginID, DestinationID;
        long double length;
        std::weak_ptr<Node> Origin, Destination;

        std::istringstream LinkParameters(*link);
        LinkParameters >> OriginID >> DestinationID >> length;
        BOOST_ASSERT_MSG(OriginID != DestinationID,
                         "Link can't have the same Origin and Destination.");

        int NodesFound = 0;

        for (auto node = Nodes.begin(); node != Nodes.end(); ++node) {
            if ((*node)->ID == OriginID) {
                Origin = *node;
                NodesFound++;
            }

            if ((*node)->ID == DestinationID) {
                Destination = *node;
                NodesFound++;
            }
        }

        BOOST_ASSERT_MSG(NodesFound == 2,
                         "Link with invalid origin and/or destination.");

        add_Link(Origin, Destination, length);
    }
}

void Topology::print_Topology(std::string TopologyFileName) {
    std::ofstream TopologyFile;
    TopologyFile.open(TopologyFileName);

    TopologyFile << "  [nodes]" << std::endl << std::endl;
    TopologyFile << "# node = ID TYPE ARCHITECTURE NUMREG" << std::endl;

    for (auto it = Nodes.begin(); it != Nodes.end(); ++it) {
        TopologyFile << "  node = " << (*it)->ID << " " << (*it)->get_NodeType() << " "
                     << (*it)->get_NodeArch() << " " << (*it)->get_NumRegenerators() << std::endl;
    }

    TopologyFile << std::endl;

    TopologyFile << "  [links]" << std::endl << std::endl;
    TopologyFile << "# -> = ORIGIN DESTINATION LENGTH" << std::endl;

    for (auto it = Links.begin(); it != Links.end(); ++it) {
        TopologyFile << "  -> = " << it->second->Origin.lock().get()->ID << " " <<
                     it->second->Destination.lock().get()->ID << " " <<
                        it->second->Length << std::endl;
    }

    TopologyFile.close();
}
