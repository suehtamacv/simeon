#include <cassert>
#include <Structure/Node.h>
#include <Devices/Amplifiers/PreAmplifier.h>
#include <Devices/Amplifiers/BoosterAmplifier.h>

Node::Node(int ID, Node_Type T, Node_Architecure A,
		   int NumRegenerators) : ID(ID), Type(T) , Architecture(A) ,
	NumRegenerators(NumRegenerators) {

	create_Devices();

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
	}
}

Node::Node_Architecure Node::get_NodeArch() {
	return Architecture;
}

void Node::create_Devices() {
}
