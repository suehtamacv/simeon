#ifdef RUN_TESTS

#include "include/Devices/Splitter.h"
#include "include/Structure/Node.h"
#include "include/Structure/Link.h"
#include <gtest/gtest.h>

TEST(DevicesTest, SplitterTest)
{
    std::shared_ptr<Node> NodeAux1 = std::make_shared<Node>(1);
    std::shared_ptr<Node> NodeAux2 = std::make_shared<Node>(2);
    std::shared_ptr<Node> NodeAux3 = std::make_shared<Node>(3);
    std::shared_ptr<Link> link12 = std::make_shared<Link>(NodeAux1, NodeAux2, 1000);
    std::shared_ptr<Link> link13 = std::make_shared<Link>(NodeAux1, NodeAux3, 1000);
    std::shared_ptr<Link> link21 = std::make_shared<Link>(NodeAux2, NodeAux1, 1000);

    Devices::Splitter Splitter1(NodeAux1.get());
    EXPECT_EQ(Splitter1.get_TransferFunction(1000)->get_TransmittanceAt(123), Splitter1.get_Gain()) << "Transfer function gain not being correctly set.";
    ASSERT_EQ(Splitter1.get_Gain(), Gain(0)) << "A splitter does not insert loss when the node does not have any neighbours.";

    NodeAux2->insert_Link(NodeAux1, link21);
    EXPECT_EQ(Splitter1.get_Gain(), Gain(0)) << "An incoming link should not affect the loss of a splitter.";
    NodeAux1->insert_Link(NodeAux2, link12);
    EXPECT_NE(Splitter1.get_Gain(), Gain(0)) << "An outcoming link should affect the loss of a splitter.";

    std::shared_ptr<Devices::Device> Splitter3 = Splitter1.clone();
    ASSERT_EQ(Splitter1.get_Gain(), Splitter3->get_Gain()) << "Splitter cloning not working correctly: gain unequal.";
    EXPECT_EQ(Splitter1.get_Noise(), Splitter3->get_Noise()) << "Splitter cloning not working correctly: noise unequal.";
    EXPECT_EQ(Splitter1.get_CapEx(), Splitter3->get_CapEx()) << "Splitter cloning not working correctly: CapEx unequal.";
    EXPECT_EQ(Splitter1.get_OpEx(), Splitter3->get_OpEx()) << "Splitter cloning not working correctly: OpEx unequal.";

    Gain origGain = Splitter1.get_Gain();
    NodeAux1->insert_Link(NodeAux3, link13);
    EXPECT_EQ(Splitter1.get_Gain(), Splitter3->get_Gain()) << "Splitter cloning not working correctly: gain unequal.";
    EXPECT_NE(Splitter1.get_Gain(), origGain) << "Splitter gain should sense the number of outcoming links of the parent node.";
}


#endif
