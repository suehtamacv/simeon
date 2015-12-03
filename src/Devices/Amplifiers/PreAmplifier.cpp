#include <Devices/Amplifiers/PreAmplifier.h>
#include <Devices/SSS.h>
#include <Structure/Node.h>

PreAmplifier::PreAmplifier(Fiber &Segment,
						   Node &Destination) : Amplifier(Gain(0)) , Destination(Destination) {
	numPorts = Destination.Links.size();
	Gain G(0);

	if (Destination.get_NodeArch() == Node::SwitchingSelect) {
		G = -SSS::SSSLoss - Segment.get_Loss();
	} else {
		G = -SSS::SSSLoss - Gain(numPorts + 1, Gain::Linear);
	}

	set_Gain(G);
}

Gain PreAmplifier::get_Gain() {
	if (Destination.get_NodeArch() == Node::BroadcastAndSelect &&
			Destination.Links.size() != numPorts)  {
		numPorts = Destination.Links.size();
		set_Gain(-SSS::SSSLoss - Gain(numPorts + 1, Gain::Linear));
	}

	return AmplifierGain;
}
