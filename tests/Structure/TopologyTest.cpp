#ifdef RUN_TESTS

#include "include/Structure.h"
#include <gtest/gtest.h>

class TopologyTest : public ::testing::Test
{
public:
    void SetUp();

    std::shared_ptr<Topology> T;

    std::weak_ptr<Node> N1, N2, N3, N4, N5, N6, N7, N8;
};

void TopologyTest::SetUp()
{
    T = std::make_shared<Topology>();

    N1 = T->add_Node(1, Node::TransparentNode, Node::SwitchingSelect, 0);
    N2 = T->add_Node(2, Node::TranslucentNode, Node::SwitchingSelect, 20);
    N3 = T->add_Node(3, Node::TransparentNode, Node::BroadcastAndSelect, 0);
    N4 = T->add_Node(4, Node::TranslucentNode, Node::BroadcastAndSelect, 40);
    N5 = T->add_Node(5, Node::TransparentNode, Node::SwitchingSelect, 0);
    N6 = T->add_Node(6, Node::TranslucentNode, Node::SwitchingSelect, 60);
    N7 = T->add_Node(7, Node::TransparentNode, Node::BroadcastAndSelect, 0);
    N8 = T->add_Node(8, Node::TranslucentNode, Node::BroadcastAndSelect, 80);
    ASSERT_EQ(T->Nodes.size(), 8) << "There should be eight nodes.";
    ASSERT_EQ(T->get_NumTranslucentNodes(), 4) << "There should be four translucent nodes.";
    ASSERT_EQ(T->get_NumRegenerators(), 200) << "There should be two hundred regenerators.";

    T->add_Link(N1, N2, 120);
    T->add_Link(N2, N1, 210);
    T->add_Link(N2, N3, 230);
    T->add_Link(N3, N4, 340);
    T->add_Link(N4, N5, 450);
    T->add_Link(N5, N4, 540);
    T->add_Link(N5, N6, 560);
    T->add_Link(N6, N7, 670);
    T->add_Link(N7, N8, 780);
    T->add_Link(N8, N1, 810);
    ASSERT_EQ(T->Links.size(), 10) << "There should be ten links.";
    ASSERT_EQ(T->get_LengthLongestLink(), 810) << "Longest link not being correctly calculated.";
}

TEST_F(TopologyTest, Constructor_EmptyTopology)
{
    Topology Top1;

    EXPECT_EQ(Top1.Nodes.size(), 0) << "There should be no nodes in an empty topology.";
    EXPECT_EQ(Top1.Links.size(), 0) << "There should be no links in an empty topology.";

    EXPECT_EQ(Top1.get_LengthLongestLink(), 0) << "The longest link of an empty topology has length zero.";
    EXPECT_EQ(Top1.get_NumRegenerators(), 0) << "There are no regenerators in an empty topology.";
    EXPECT_EQ(Top1.get_NumTranslucentNodes(), 0) << "There are no translucent nodes in an empty topology.";
    EXPECT_EQ(Top1.get_CapEx(), 0) << "The CapEx of an empty topology should be zero.";
    EXPECT_EQ(Top1.get_OpEx(), 0) << "The OpEx of an empty topology should be zero.";

    Topology Top2(Top1); //Creating copy.

    EXPECT_EQ(Top2.Nodes.size(), 0) << "There should be no nodes in an empty topology.";
    EXPECT_EQ(Top2.Links.size(), 0) << "There should be no links in an empty topology.";

    EXPECT_EQ(Top2.get_LengthLongestLink(), 0) << "The longest link of an empty topology has length zero.";
    EXPECT_EQ(Top2.get_NumRegenerators(), 0) << "There are no regenerators in an empty topology.";
    EXPECT_EQ(Top2.get_NumTranslucentNodes(), 0) << "There are no translucent nodes in an empty topology.";
    EXPECT_EQ(Top2.get_CapEx(), 0) << "The CapEx of an empty topology should be zero.";
    EXPECT_EQ(Top2.get_OpEx(), 0) << "The OpEx of an empty topology should be zero.";
}

TEST_F(TopologyTest, Topology_CopyConstructor)
{
    Topology T_Copy(*T);

    ASSERT_EQ(T_Copy.Nodes.size(), T->Nodes.size()) << "Topologies should have the same number of nodes.";
    for (size_t n = 0; n < T_Copy.Nodes.size(); ++n)
        {
        EXPECT_EQ(T_Copy.Nodes[n]->ID, T->Nodes[n]->ID) << "Node " << *(T_Copy.Nodes[n]) << " and Node " << *(T->Nodes[n]) << " should have equal IDs.";
        EXPECT_EQ(T_Copy.Nodes[n]->get_NodeType(), T->Nodes[n]->get_NodeType()) << "Node " << *(T_Copy.Nodes[n]) << " and Node " << *(T->Nodes[n]) << " should have equal types.";
        EXPECT_EQ(T_Copy.Nodes[n]->get_NodeArch(), T->Nodes[n]->get_NodeArch()) << "Node " << *(T_Copy.Nodes[n]) << " and Node " << *(T->Nodes[n]) << " should have equal architectures.";
        EXPECT_EQ(T_Copy.Nodes[n]->get_NumRegenerators(), T->Nodes[n]->get_NumRegenerators()) << "Node " << *(T_Copy.Nodes[n]) << " and Node " << *(T->Nodes[n]) << " should have equal number of regenerators.";
        }

    ASSERT_EQ(T_Copy.Links.size(), T->Links.size()) << "Topologies should have the same number of links.";
    for (auto &linkIterator : T->Links)
        {
        EXPECT_EQ(*(T->Links[linkIterator.first]->Origin.lock()), *(T_Copy.Links[linkIterator.first]->Origin.lock())) << "Links should have the same origin node.";
        EXPECT_EQ(*(T->Links[linkIterator.first]->Destination.lock()), *(T_Copy.Links[linkIterator.first]->Destination.lock())) << "Links should have the same origin node.";
        EXPECT_EQ(T->Links[linkIterator.first]->Length, T_Copy.Links[linkIterator.first]->Length) << "Links should have the same length.";
        }

    EXPECT_EQ(T_Copy.get_NumTranslucentNodes(), 4) << "There should be four translucent nodes.";
    EXPECT_EQ(T_Copy.get_NumRegenerators(), 200) << "There should be two hundred regenerators.";
    EXPECT_EQ(T_Copy.get_LengthLongestLink(), 810) << "Longest link not being correctly calculated.";
}

#endif
