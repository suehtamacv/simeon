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
	}
}
