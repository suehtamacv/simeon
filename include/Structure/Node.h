#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>
#include <Structure/Link.h>

class Node {
  public:
	Node();

	std::vector<Node *> Neighbours;
	std::vector<std::unique_ptr<Link>> Links;
};

#endif // NODE_H
