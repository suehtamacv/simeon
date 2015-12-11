#include <boost/assert.hpp>
#include <Structure/Node.h>
#include <Structure/Link.h>
#include <Devices/Amplifiers/PreAmplifier.h>
#include <Devices/Amplifiers/BoosterAmplifier.h>
#include <Devices/SSS.h>
#include <Devices/Splitter.h>

Node::Node(int ID, Node_Type T, Node_Architecure A) : ID(ID), Type(T) ,
    Architecture(A) {
    create_Devices();
}

Node::Node(const Node &node) : ID(node.ID) {
    Type = node.Type;
    Architecture = node.Architecture;
    NumRegenerators = node.NumRegenerators;
    NumAvailableRegenerators = NumRegenerators;

    for (auto link : node.Links) {
        std::shared_ptr<Link> newlink = std::shared_ptr<Link>(new Link(*link));
        insert_Link(newlink->Destination, newlink);
    }

    for (auto device : node.Devices) {
        Devices.push_back(device->clone());
    }
}

bool Node::operator ==(const Node &N) const {
    return (ID == N.ID);
}

bool Node::operator <(const Node &N) const {
    return (ID < N.ID);
}

void Node::insert_Link(std::weak_ptr<Node> N, std::shared_ptr<Link> Link) {
    bool LinkExists = false;

    for (auto it : Neighbours) {
        if (it.lock() == N.lock()) {
            LinkExists = true;
            break;
        }
    }

    if (!LinkExists) {
        Neighbours.push_back(N);
        Links.push_back(Link);

        if (Architecture == BroadcastAndSelect) {
            BOOST_ASSERT_MSG((*Devices.front()).DevType == Device::SplitterDevice,
                             "In a B&S node, the first device is a spliiter.");
            static_cast<Splitter &>(*Devices.front()).set_NumPorts(Links.size());
        }
    }
}

Node::Node_Architecure Node::get_NodeArch() {
    return Architecture;
}

Node::Node_Type Node::get_NodeType() {
    return Type;
}

unsigned int Node::get_NumRegenerators() {
    return NumRegenerators;
}

unsigned int Node::get_NumAvailableRegenerators() {
    return NumAvailableRegenerators;
}

void Node::create_Devices() {
    //Switching element - entrance
    switch (Architecture) {
        case BroadcastAndSelect:
            Devices.push_back(std::shared_ptr<Device>(new Splitter(Links.size())));
            break;

        case SwitchingSelect:
            Devices.push_back(std::shared_ptr<Device>(new SSS()));
            break;
    }

    //Switching element - exit
    Devices.push_back(std::shared_ptr<Device>(new SSS()));

    //Booster Amplifier
    Devices.push_back(std::shared_ptr<Device>(new BoosterAmplifier()));
}

Signal Node::bypass(Signal S) {
    for (auto it = Devices.begin(); it != Devices.end(); ++it) {
        S *= (*it)->get_Gain();
        S += (*it)->get_Noise();
    }

    return S;
}

Signal Node::drop(Signal S) {
    for (auto it : Devices) {
        S *= it->get_Gain();
        S += it->get_Noise();

        if ((it->DevType == Device::SplitterDevice) ||
                (it->DevType == Device::SSSDevice)) {
            break;
        }
    }

    return S;
}

Signal Node::add(Signal S) {
    auto it = Devices.begin();

    while (((*it)->DevType != Device::SplitterDevice) &&
            ((*it)->DevType != Device::SSSDevice)) {
        it++;
    }

    it++;

    for (; it != Devices.end(); ++it) {
        S *= (*it)->get_Gain();
        S += (*it)->get_Noise();
    }

    return S;
}

void Node::set_NumRegenerators(unsigned int NReg) {
    NumRegenerators = NReg;
    NumAvailableRegenerators = NumRegenerators;
}

bool Node::isNeighbour(std::weak_ptr<Node> N) {
    for (auto it : Neighbours) {
        if (N.lock() == it.lock()) {
            return true;
        }
    }

    return false;
}

void Node::set_NodeType(Node_Type T) {
    Type = T;
}
