#ifdef RUN_TESTS

#include "include/Structure/Link.h"
#include "include/Structure/Slot.h"
#include "include/Structure/Topology.h"
#include "Calls/Call.h"
#include "Devices/Device.h"
#include <gtest/gtest.h>

class LinkTest : public ::testing::Test
{
public:
    void SetUp();

    std::shared_ptr<Topology> T;
    std::weak_ptr<Node> N1, N2, N3, N4;
};

void LinkTest::SetUp()
{
    T = std::make_shared<Topology>();
    T->set_avgSpanLength(100);

    N1 = T->add_Node(1);
    N2 = T->add_Node(2);
    N3 = T->add_Node(3);
    N4 = T->add_Node(4);
}

TEST_F(LinkTest, Constructor)
{
    std::shared_ptr<Link> link1 = T->add_Link(N1, N2, 1000).lock();
    EXPECT_TRUE(link1->is_LinkActive()) << "Link should start as active.";
    EXPECT_EQ(*(link1->Origin.lock()), *(N1.lock())) << "Origin node not being correctly set.";
    EXPECT_EQ(*(link1->Destination.lock()), *(N2.lock())) << "Destination node not being correctly set.";
    EXPECT_EQ(link1->Length, 1000) << "Link length not being correctly set.";

    ASSERT_EQ(link1->Slots.size(), Link::NumSlots) << "Link slots aren't being correctly created.";
    for (int s = 0; s < Link::NumSlots; ++s)
        {
        EXPECT_TRUE(link1->Slots[s]->isFree) << "Link slot should be initialized as free.";
        EXPECT_TRUE(link1->isSlotFree(s)) << "Link slot should be initialized as free.";
        }

    std::shared_ptr<Link> link2 = T->add_Link(N4, N1, 2000).lock();
    EXPECT_TRUE(link2->is_LinkActive()) << "Link should start as active.";
    EXPECT_EQ(*(link2->Origin.lock()), *(N4.lock())) << "Origin node not being correctly set.";
    EXPECT_EQ(*(link2->Destination.lock()), *(N1.lock())) << "Destination node not being correctly set.";
    EXPECT_EQ(link2->Length, 2000) << "Link length not being correctly set.";

    std::shared_ptr<Link> link3 = std::make_shared<Link>(*link2);
    EXPECT_TRUE(link3->is_LinkActive()) << "Link should start as active.";
    EXPECT_EQ(*(link3->Origin.lock()), *(link2->Origin.lock())) << "Copy constructor: origin node not being correctly set.";
    EXPECT_EQ(*(link3->Destination.lock()), *(link2->Destination.lock())) << "Copy constructor: destination node not being correctly set.";
    EXPECT_EQ(link3->Length, link2->Length) << "Copy constructor: link length not being correctly set.";
}

TEST_F(LinkTest, Activation)
{
    std::shared_ptr<Link> link = T->add_Link(N2, N3, 1000).lock();

    EXPECT_TRUE(link->is_LinkActive()) << "Link should start as active.";
    link->set_LinkInactive();
    EXPECT_FALSE(link->is_LinkActive()) << "Link is not being deactivated.";
    link->set_LinkActive();
    EXPECT_TRUE(link->is_LinkActive()) << "Link is not being reactivated.";
}

TEST_F(LinkTest, AvailabilityOccupability)
{
    std::shared_ptr<Link> link = T->add_Link(N2, N3, 1000).lock();

    EXPECT_EQ(link->get_Availability(), Link::NumSlots) << "All slots should be free when creating a new link.";
    EXPECT_EQ(link->get_Occupability(), 0) << "No slots should be occupied when creating a new link.";

    link->Slots[0]->useSlot();
    link->Slots[1]->useSlot();
    link->Slots[Link::NumSlots - 1]->useSlot();
    EXPECT_EQ(link->get_Availability(), Link::NumSlots - 3) << "Availability measure not working as expected.";
    EXPECT_EQ(link->get_Occupability(), 3) << "Occupability measure not working as expected.";

    link->Slots[0]->freeSlot();
    EXPECT_EQ(link->get_Availability(), Link::NumSlots - 2) << "Availability measure not working as expected.";
    EXPECT_EQ(link->get_Occupability(), 2) << "Occupability measure not working as expected.";

    link->Slots[Link::NumSlots - 1]->freeSlot();
    EXPECT_EQ(link->get_Availability(), Link::NumSlots - 1) << "Availability measure not working as expected.";
    EXPECT_EQ(link->get_Occupability(), 1) << "Occupability measure not working as expected.";

    link->Slots[1]->freeSlot();
    EXPECT_EQ(link->get_Availability(), Link::NumSlots) << "Availability measure not working as expected.";
    EXPECT_EQ(link->get_Occupability(), 0) << "Occupability measure not working as expected.";
}

TEST_F(LinkTest, Contiguity)
{
    std::shared_ptr<Link> link = T->add_Link(N2, N3, 1000).lock();

    //Setting up a call
    ModulationScheme scheme = *(ModulationScheme::DefaultSchemes.begin());
    TransmissionBitrate br = TransmissionBitrate::DefaultBitrates.back();
    std::shared_ptr<Call> C = std::make_shared<Call>(N2, N3, br, scheme);
    int reqSlots = scheme.get_NumSlots(br);

    EXPECT_EQ(link->get_Contiguity(C), Link::NumSlots - reqSlots + 1) << "In a link completely free, there should be NumSlots - reqSlots + 1 possible ways of allocating a call that requires reqSlots.";
    EXPECT_LT(reqSlots, Link::NumSlots) << "Possible requisition asks for more slots than there are available in a link.";

    for (int s = 1; s < reqSlots + 1; ++s) //Leaving one slot free and then reqSlot occupied slots.
        {
        link->Slots.at(s)->useSlot();
        }
    EXPECT_EQ(link->get_Contiguity(C), Link::NumSlots - 2 * reqSlots) << "Contiguity measure not working as expected.";

    for (int s = 1; s < reqSlots + 1; ++s)
        {
        link->Slots.at(s)->freeSlot();
        }
    EXPECT_EQ(link->get_Contiguity(C), Link::NumSlots - reqSlots + 1) << "In a link completely free, there should be NumSlots - reqSlots + 1 possible ways of allocating a call that requires reqSlots.";
}

TEST_F(LinkTest, Devices)
{
    T->set_avgSpanLength(100);
    std::shared_ptr<Link> link = T->add_Link(N1, N4, 1000).lock();

    ASSERT_FALSE(link->Devices.empty()) << "Link devices should be created.";

    int numFibers = 0;
    int numAmplifiers = 0;
    for (std::shared_ptr<Devices::Device> device : link->Devices)
        {
        if (device->DevType == Devices::Device::FiberDevice)
            {
            ++numFibers;
            }
        if (device->DevType == Devices::Device::AmplifierDevice)
            {
            ++numAmplifiers;
            }
        }

    EXPECT_EQ(numFibers, numAmplifiers) << "There should be one fiber segment to each amplifier.";
    EXPECT_EQ(numFibers, link->numLineAmplifiers + 1) << "Link amplifiers should be composed by one booster amplifier among all line amplifiers.";

    size_t numDevices = link->Devices.size();
    link->set_AvgSpanLength(10);
    EXPECT_NE(numDevices, link->Devices.size()) << "Setting average span length has no effect.";
    link->set_AvgSpanLength(100);
    EXPECT_EQ(numDevices, link->Devices.size()) << "Number of devices in a link is varying.";
}

#endif
