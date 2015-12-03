#include <cassert>
#include <Structure/Node.h>

Node::Node(int ID, Node_Type T, Node_Architecure A,
		   int NumRegenerators) : ID(ID), Type(T) , Architecture(A) ,
	NumRegenerators(NumRegenerators) {
}

bool Node::operator ==(Node *N) {
	if (ID == N->ID) {
		return true;
	}

	return false;
}

void Node::insert_Link(Node *N, std::shared_ptr<Link> Link) {
	bool LinkExists = false;

	for (auto it = Neighbours.begin(); it != Neighbours.end(); ++it) {
		if (*it == N) {
			LinkExists = true;
			break;
		}
	}

	if (!LinkExists) {
		Neighbours.push_back(N);
		Links.push_back(Link);
		create_Devices(Link);
	}
}

void Node::create_Devices(std::shared_ptr<Link> Link) {
	Gain PreampGain(Link->AvgSpanLength / (Link->numLineAmplifiers + 1));

	if (Architecture == SwitchingSelect) {
		PreampGain = PreampGain + SSS::SSSLoss;
	} else if (Architecture == BroadcastAndSelect) {
		PreampGain = PreampGain + Gain(Neighbours.size() + 1, Gain::Linear);
	}

	std::unique_ptr<std::vector<std::unique_ptr<Device>>> LinkDevices(
		new std::vector<std::unique_ptr<Device>>);

	//Pre-amplifier
	LinkDevices->push_back(std::unique_ptr<Device>(new Amplifier(PreampGain)));
}
