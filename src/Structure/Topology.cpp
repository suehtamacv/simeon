#include <Structure/Topology.h>
#include <boost/assert.hpp>
#include <boost/program_options.hpp>
#include <fstream>
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

std::weak_ptr<Node> Topology::add_Node(Node::Node_Type Type,
                                       Node::Node_Architecure Arch, int NumReg) {
    Nodes.push_back(std::shared_ptr<Node>(new Node(Nodes.size() + 1, Type, Arch)));
    Nodes.back()->set_NumRegenerators(NumReg);
    return (std::weak_ptr<Node>) Nodes.back();
}

std::weak_ptr<Link> Topology::add_Link(std::weak_ptr<Node> Origin,
                                       std::weak_ptr<Node> Destination, long double Length) {
    Links.push_back(std::shared_ptr<Link>(new Link(Origin, Destination, Length)));
    Origin.lock()->insert_Link(Destination.lock().get(), Links.back());
    return (std::weak_ptr<Link>) Links.back();
}

void Topology::read_Topology(std::string TopologyFileName) {
    boost::program_options::options_description NodesList("nodes");
    NodesList.add_options()
    ("node", "Node Description");

    boost::program_options::options_description LinksList("links");
    LinksList.add_options()
    ("->", "Unidirectional Link Description")
    ("<->", "Bidirectional Link Description");

    boost::program_options::options_description TopologyDescription("topology");
    TopologyDescription.add(NodesList).add(LinksList);

    boost::program_options::variables_map VariablesMap;

    boost::program_options::store(
        boost::program_options::parse_config_file<char>(
            TopologyFileName.c_str(), TopologyDescription),
        VariablesMap);
}

void Topology::print_Topology(std::string TopologyFileName) {
    std::ofstream TopologyFile;
    TopologyFile.open(TopologyFileName);

    TopologyFile << "  [topology.nodes]" << std::endl << std::endl;
    TopologyFile << "# node = ID ARCHITECTURE TYPE NUMREG" << std::endl;

    for (auto it = Nodes.begin(); it != Nodes.end(); ++it) {
        TopologyFile << "  node = " << (*it)->ID << " " << (*it)->get_NodeArch() << " "
                     << (*it)->get_NodeType() << " " << (*it)->get_NumRegenerators() << std::endl;
    }

    TopologyFile << std::endl;

    TopologyFile << "  [topology.links]" << std::endl << std::endl;
    TopologyFile << "# -> = ORIGIN DESTINATION LENGTH" << std::endl;

    for (auto it = Links.begin(); it != Links.end(); ++it) {
        TopologyFile << "  -> = " << (*it)->Origin.lock().get()->ID << " " <<
                     (*it)->Destination.lock().get()->ID << " " << (*it)->Length << std::endl;
    }

}
