#ifdef RUN_TESTS

#include "include/Structure/Node.h"
#include "include/Structure/Link.h"
#include "include/Structure/Topology.h"
#include <gtest/gtest.h>

class NodeTest : public ::testing::Test
{
public:
    void SetUp();
    std::shared_ptr<Topology> T;
};

void NodeTest::SetUp()
{
    T = std::make_shared<Topology>();
}

TEST_F(NodeTest, StandaloneConstructor)
{
    Node N1(1);
    EXPECT_TRUE(N1.is_NodeActive()) << "Node should start as active.";
    EXPECT_EQ(N1.ID, 1) << "Node ID not being correctly set.";
    EXPECT_EQ(N1.get_NodeType(), Node::TransparentNode) << "Node should be transparent by default.";
    EXPECT_EQ(N1.get_NumRegenerators(), 0) << "There should be no regenerators in a transparent node.";
    EXPECT_EQ(N1.get_NumAvailableRegenerators(), 0) << "There should be no available regenerators in a transparent node.";
    EXPECT_EQ(N1.get_TotalNumRequestedRegenerators(), 0) << "No regenerators should ever be used in a transparent node.";
    EXPECT_EQ(N1.get_NumMaxSimultUsedRegenerators(), 0) << "No regenerators should ever be used in a transparent node.";

    Node N1_Copy(N1);
    EXPECT_EQ(N1, N1_Copy) << "Copy constructor not working as it should.";
    EXPECT_TRUE(N1_Copy.is_NodeActive()) << "Node should start as active.";
    EXPECT_EQ(N1_Copy.ID, 1) << "Node ID not being correctly set.";
    EXPECT_EQ(N1_Copy.get_NodeType(), Node::TransparentNode) << "Node should be transparent by default.";
    EXPECT_EQ(N1_Copy.get_NumRegenerators(), 0) << "There should be no regenerators in a transparent node.";
    EXPECT_EQ(N1_Copy.get_NumAvailableRegenerators(), 0) << "There should be no available regenerators in a transparent node.";
    EXPECT_EQ(N1_Copy.get_TotalNumRequestedRegenerators(), 0) << "No regenerators should ever be used in a transparent node.";
    EXPECT_EQ(N1_Copy.get_NumMaxSimultUsedRegenerators(), 0) << "No regenerators should ever be used in a transparent node.";

    Node N2(2, Node::TranslucentNode);
    EXPECT_EQ(N2.ID, 2) << "Node ID not being correctly set.";
    EXPECT_TRUE(N2.is_NodeActive()) << "Node should start as active.";
    EXPECT_EQ(N2.get_NodeType(), Node::TranslucentNode) << "Node should be transparent by default.";
    EXPECT_EQ(N2.get_NumRegenerators(), 0) << "By default, there should be no regenerators even in a translucent node.";
    EXPECT_EQ(N2.get_NumAvailableRegenerators(), 0) << "By default, there should be no available regenerators even in a translucent node.";
    EXPECT_EQ(N2.get_TotalNumRequestedRegenerators(), 0) << "By default, no regenerators should have been requested in a translucent node.";
    EXPECT_EQ(N2.get_NumMaxSimultUsedRegenerators(), 0) << "By default, no regenerators should have been used in a translucent node.";
}

TEST_F(NodeTest, IntegratedConstructor)
{
    std::shared_ptr<Node> N1 = T->add_Node(1, Node::TransparentNode, Node::SwitchingSelect).lock();
    EXPECT_EQ(N1->ID, 1) << "Node ID not being correctly set.";
    EXPECT_EQ(N1->get_NodeType(), Node::TransparentNode) << "Node should be transparent by default.";
    EXPECT_EQ(N1->get_NodeArch(), Node::SwitchingSelect) << "Node architecture is not being set.";
    EXPECT_EQ(N1->get_NumRegenerators(), 0) << "There should be no regenerators in a transparent node.";
    EXPECT_TRUE(N1->Regenerators.empty()) << "No regenerators should have been created.";
    EXPECT_EQ(N1->get_NumAvailableRegenerators(), 0) << "There should be no available regenerators in a transparent node.";
    EXPECT_EQ(N1->get_TotalNumRequestedRegenerators(), 0) << "No regenerators should ever be used in a transparent node.";
    EXPECT_EQ(N1->get_NumMaxSimultUsedRegenerators(), 0) << "No regenerators should ever be used in a transparent node.";

    std::shared_ptr<Node> N2 = T->add_Node(2, Node::TranslucentNode, Node::BroadcastAndSelect).lock();
    EXPECT_EQ(N2->ID, 2) << "Node ID not being correctly set.";
    EXPECT_EQ(N2->get_NodeType(), Node::TranslucentNode) << "Node should be transparent by default.";
    EXPECT_EQ(N2->get_NodeArch(), Node::BroadcastAndSelect) << "Node architecture is not being set.";
    EXPECT_EQ(N2->get_NumRegenerators(), 0) << "By default, there should be no regenerators even in a translucent node.";
    EXPECT_TRUE(N2->Regenerators.empty()) << "No regenerators should have been created.";
    EXPECT_EQ(N2->get_NumAvailableRegenerators(), 0) << "By default, there should be no available regenerators even in a translucent node.";
    EXPECT_EQ(N2->get_TotalNumRequestedRegenerators(), 0) << "By default, no regenerators should have been requested in a translucent node.";
    EXPECT_EQ(N2->get_NumMaxSimultUsedRegenerators(), 0) << "By default, no regenerators should have been used in a translucent node.";

    std::shared_ptr<Node> N3 = T->add_Node(3, Node::TranslucentNode, Node::SwitchingSelect, 100).lock();
    EXPECT_EQ(N3->ID, 3) << "Node ID not being correctly set.";
    EXPECT_EQ(N3->get_NodeType(), Node::TranslucentNode) << "Node should be transparent by default.";
    EXPECT_EQ(N3->get_NodeArch(), Node::SwitchingSelect) << "Node architecture is not being set.";
    EXPECT_EQ(N3->get_NumRegenerators(), 100) << "Regenerators are not being created.";
    EXPECT_EQ(N3->Regenerators.size(), 100) << "Regenerators are not being created.";
    EXPECT_EQ(N3->get_NumAvailableRegenerators(), 100) << "Regenerators should be created as available";
    EXPECT_EQ(N3->get_TotalNumRequestedRegenerators(), 0) << "No regenerators should have been requested.";
    EXPECT_EQ(N3->get_NumMaxSimultUsedRegenerators(), 0) << "No regenerators should have been used.";

}

TEST_F(NodeTest, Activation)
{
    std::shared_ptr<Node> N = T->add_Node(0).lock();

    EXPECT_TRUE(N->is_NodeActive()) << "Node should start as active.";
    N->set_NodeInactive();
    EXPECT_FALSE(N->is_NodeActive()) << "Node is not being deactivated.";
    N->set_NodeActive();
    EXPECT_TRUE(N->is_NodeActive()) << "Node is not being reactivated.";
}

TEST_F(NodeTest, Regenerators)
{
    std::shared_ptr<Node> N = T->add_Node(0, Node::TranslucentNode, Node::SwitchingSelect, 50).lock();

    EXPECT_EQ(N->get_NumRegenerators(), 50) << "Regenerators were not created.";
    EXPECT_EQ(N->get_NumAvailableRegenerators(), 50) << "Regenerators were not created as available.";
    EXPECT_EQ(N->get_NumMaxSimultUsedRegenerators(), 0) << "Regenerators should not have been used.";
    EXPECT_EQ(N->get_TotalNumRequestedRegenerators(), 0) << "Regenerators should not have been used.";

    N->set_NumRegenerators(100);
    EXPECT_EQ(N->get_NumRegenerators(), 100) << "Regenerators were not created.";
    EXPECT_EQ(N->get_NumAvailableRegenerators(), 100) << "Regenerators were not created as available.";
    EXPECT_EQ(N->get_NumMaxSimultUsedRegenerators(), 0) << "Regenerators should not have been used.";
    EXPECT_EQ(N->get_TotalNumRequestedRegenerators(), 0) << "Regenerators should not have been used.";

    N->request_Regenerators(5);
    EXPECT_EQ(N->get_NumRegenerators(), 100) << "Number of regenerators should not be affected by their usage.";
    EXPECT_EQ(N->get_NumAvailableRegenerators(), 95) << "Regenerators not being correctly marked as busy.";
    EXPECT_EQ(N->get_NumMaxSimultUsedRegenerators(), 5) << "Simultaneously used regenerators are not being counted.";
    EXPECT_EQ(N->get_TotalNumRequestedRegenerators(), 5) << "Used regenerators are not being counted.";

    N->request_Regenerators(10);
    EXPECT_EQ(N->get_NumRegenerators(), 100) << "Number of regenerators should not be affected by their usage.";
    EXPECT_EQ(N->get_NumAvailableRegenerators(), 85) << "Regenerators not being correctly marked as busy.";
    EXPECT_EQ(N->get_NumMaxSimultUsedRegenerators(), 15) << "Simultaneously used regenerators are not being counted.";
    EXPECT_EQ(N->get_TotalNumRequestedRegenerators(), 15) << "Used regenerators are not being counted.";

    N->free_Regenerators(10);
    EXPECT_EQ(N->get_NumRegenerators(), 100) << "Number of regenerators should not be affected by their usage.";
    EXPECT_EQ(N->get_NumAvailableRegenerators(), 95) << "Regenerators not being correctly marked as busy.";
    EXPECT_EQ(N->get_NumMaxSimultUsedRegenerators(), 15) << "Simultaneously used regenerators are not being counted.";
    EXPECT_EQ(N->get_TotalNumRequestedRegenerators(), 15) << "Used regenerators are not being counted.";

    N->request_Regenerators(5);
    EXPECT_EQ(N->get_NumRegenerators(), 100) << "Number of regenerators should not be affected by their usage.";
    EXPECT_EQ(N->get_NumAvailableRegenerators(), 90) << "Regenerators not being correctly marked as busy.";
    EXPECT_EQ(N->get_NumMaxSimultUsedRegenerators(), 15) << "Simultaneously used regenerators are not being counted.";
    EXPECT_EQ(N->get_TotalNumRequestedRegenerators(), 20) << "Used regenerators are not being counted.";

    N->free_Regenerators(5);
    N->free_Regenerators(5);
    EXPECT_EQ(N->get_NumRegenerators(), 100) << "Number of regenerators should not be affected by their usage.";
    EXPECT_EQ(N->get_NumAvailableRegenerators(), 100) << "Regenerators not being correctly marked as busy.";
    EXPECT_EQ(N->get_NumMaxSimultUsedRegenerators(), 15) << "Simultaneously used regenerators are not being counted.";
    EXPECT_EQ(N->get_TotalNumRequestedRegenerators(), 20) << "Used regenerators are not being counted.";
}

#endif
