#include <boost/assert.hpp>
#include <fstream>
#include <Structure/Topology.h>
#include <Structure/Node.h>

Topology::Topology(std::string TopologyFileName) {
    std::ifstream TopologyFile;
    TopologyFile.open(TopologyFileName);
    BOOST_ASSERT_MSG(TopologyFile.is_open(), "Topology file could not be open.");


}

