#ifndef NODE_H
#define NODE_H

#include <map>
#include <memory>
#include <vector>
#include <Devices/Device.h>
#include <Devices/Amplifiers/Amplifier.h>
#include <Devices/Splitter.h>
#include <Devices/SSS.h>
#include <Structure/Link.h>

class Node {
  public:
	/**
	* @brief The Node_Type enum is used to set the type of node.
	*
	* Use TransparentNode if the node is transparent, with no regenerators, TranslucentNode if the node is
	* translucent, with a limited amount of regenerators, or OpaqueNode if the node is opaque, that is,
	* has a infinity amount of regenerators.
	*/
	enum Node_Type {
		TransparentNode, TranslucentNode, OpaqueNode
	};
	/**
	 * @brief The Node_Architecure enum is used to set the type of node.
	 *
	 * There are two architectures, Broadcast And Select, that uses splitters and SSS, and Switching Select,
	 * that only uses SSS devices.
	 */
	enum Node_Architecure {
		BroadcastAndSelect, SwitchingSelect
	};

	Node(int ID, Node_Type T = TransparentNode, Node_Architecure A = SwitchingSelect, int NumRegenerators = 0);

	const int ID;
	bool operator==(Node *);

	std::vector<Node *> Neighbours;
	std::vector<std::shared_ptr<Link>> Links;
	std::map<std::weak_ptr<Link> , std::unique_ptr<std::vector<Device>>> Devices;

	void insert_Link(Node *N, std::shared_ptr<Link> Link);

  private:
	Node_Type Type;
	Node_Architecure Architecture;
	int NumRegenerators;
};

#endif // NODE_H
