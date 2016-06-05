#ifdef RUN_TESTS

#include "include/Calls/CallGenerator.h"
#include "include/Calls/Call.h"
#include "include/Calls/Event.h"
#include <gtest/gtest.h>

class CallGeneratorTest : public ::testing::Test
{
public:
    void SetUp();

    static constexpr int numCalls = 20;
    std::shared_ptr<Topology> T;
    std::shared_ptr<CallGenerator> CG;
    std::shared_ptr<Call> Calls[numCalls];
};

void CallGeneratorTest::SetUp()
{
    T = std::make_shared<Topology>();

    T->add_Node(1);
    T->add_Node(2);
    T->add_Node(3);

    CG = std::make_shared<CallGenerator>(T, 100);
    EXPECT_EQ(CG->simulationTime, 0) << "Call Generator internal time should start at zero.";

    for (unsigned c = 0; c < numCalls; ++c)
        {
        Calls[c] = CG->generate_Call();
        }
}

TEST_F(CallGeneratorTest, Constructor)
{
    EXPECT_EQ(CG->T, T) << "Constructor not working as it should.";
    EXPECT_EQ(CG->h, 100) << "Constructor not working as it should.";
}

TEST_F(CallGeneratorTest, SettingValues)
{
    //Network load setting
    CG->set_Load(200);
    EXPECT_EQ(CG->h, 200) << "Network load is not being set.";
}

TEST_F(CallGeneratorTest, CallGeneration)
{
    //Tests whether the generated events make sense
    for (unsigned c = 0; c < numCalls; ++c)
        {
        EXPECT_GT(*(Calls[c]->CallEnding.lock()), *(Calls[c]->CallRequisition.lock())) << "Call " << c << " should end after it starts.";
        EXPECT_NE(*(Calls[c]->Origin.lock()), *(Calls[c]->Destination.lock())) << "Call " << c << " must be stablished between different source and destination nodes.";
        if (c != 0)
            {
            EXPECT_LT(*(Calls[c - 1]->CallRequisition.lock()), *(Calls[c]->CallRequisition.lock())) << "Call " << c - 1 << " should start before Call " << c << ".";
            }
        }

    //Tests whether the events are being correctly being saved into the priority queue
    EXPECT_EQ(CG->Events.size(), 2 * numCalls) << "There should be two events per generated call.";
    EXPECT_EQ(*(Calls[0]->CallRequisition.lock()), *(CG->Events.top())) << "The first event should be the beginning of the first call";
}

#endif
