#include <boost/assert.hpp>
#include <Structure/Node.h>
#include <Devices/Amplifiers/PreAmplifier.h>
#include <Devices/Amplifiers/BoosterAmplifier.h>
#include <Devices/SSS.h>
#include <Devices/Splitter.h>

Node::Node(int ID, Node_Type T, Node_Architecure A) : ID(ID), Type(T) ,
    Architecture(A) {
    create_Devices();
}

bool Node::operator ==(Node *N) {
    if (ID == N->ID) {
        return true;
    }

    return false;
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
            BOOST_ASSERT_MSG((*Devices.front()).T == Device::SplitterDevice,
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

void Node::create_Devices() {
    //Switching element - entrance
    switch (Architecture) {
        case BroadcastAndSelect:
            Devices.push_back(std::unique_ptr<Device>(new Splitter(Links.size())));
            break;

        case SwitchingSelect:
            Devices.push_back(std::unique_ptr<Device>(new SSS()));
            break;
    }

    //Switching element - exit
    Devices.push_back(std::unique_ptr<Device>(new SSS()));

    //Booster Amplifier
    Devices.push_back(std::unique_ptr<Device>(new BoosterAmplifier()));
}

Signal Node::bypass(Signal S) {
    for (auto it = Devices.begin(); it != Devices.end(); ++it) {
        S *= (*it)->get_Gain();
        S *= (*it)->get_Loss();
        S += (*it)->get_Noise();
    }

    return S;
}

Signal Node::add(Signal S) {
    for (auto it = Devices.begin(); it != Devices.end(); ++it) {
        S *= (*it)->get_Gain();
        S *= (*it)->get_Loss();
        S += (*it)->get_Noise();

        if ((*it)->T == Device::SplitterDevice || (*it)->T == Device::SSSDevice) {
            break;
        }
    }

    return S;
}

Signal Node::drop(Signal S) {
    bool foundExit = false;

    for (auto it = Devices.begin(); it != Devices.end(); ++it) {
        if (!foundExit && (*it)->T != Device::SplitterDevice &&
                (*it)->T != Device::SSSDevice) {
            foundExit = true;
            continue;
        }

        S *= (*it)->get_Gain();
        S *= (*it)->get_Loss();
        S += (*it)->get_Noise();
    }

    return S;
}

void Node::set_NumRegenerators(unsigned int NReg) {
    NumRegenerators = NReg;
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
