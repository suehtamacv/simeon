#include <Devices/Amplifiers/PreAmplifier.h>
#include <Devices/Fiber.h>
#include <Devices/SSS.h>
#include <Structure/Node.h>

PreAmplifier::PreAmplifier(Fiber &Segment, Node &Destination) : EDFA(Gain(0)) ,
    Destination(Destination), Segment(Segment) {
    numPorts = Destination.Links.size();

    if (Destination.get_NodeArch() == Node::SwitchingSelect) {
        set_Gain(-Segment.get_Gain() - SSS::SSSLoss);
    } else {
        set_Gain(-Segment.get_Gain() - Gain(numPorts + 1, Gain::Linear));
    }
}

Gain PreAmplifier::get_Gain() {
    if (Destination.get_NodeArch() == Node::BroadcastAndSelect &&
            Destination.Links.size() != numPorts)  {
        numPorts = Destination.Links.size();
        set_Gain(-Segment.get_Gain() - Gain(numPorts + 1, Gain::Linear));
    }

    return AmplifierGain;
}

std::shared_ptr<Device> PreAmplifier::clone() {
    return std::shared_ptr<Device>(new PreAmplifier(*this));
}
