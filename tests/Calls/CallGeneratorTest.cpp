#ifdef RUN_TESTS

#include "include/Calls/CallGenerator.h"
#include "include/Calls/Call.h"
#include "include/Calls/Event.h"
#include <gtest/gtest.h>

TEST(CallGeneratorTest, Constructor)
{
    //Setting up
    std::shared_ptr<Topology> T = std::make_shared<Topology>();
    T->add_Node(1);
    T->add_Node(2);
    T->add_Node(3);

    CallGenerator CG(T, 100);
    EXPECT_EQ(CG.T, T) << "Constructor not working as it should.";
    EXPECT_EQ(CG.h, 100) << "Constructor not working as it should.";
    EXPECT_EQ(CG.simulationTime, 0) << "Constructor not working as it should.";
}

TEST(CallGeneratorTest, SettingValues)
{
    //Setting up
    std::shared_ptr<Topology> T = std::make_shared<Topology>();
    T->add_Node(1);
    T->add_Node(2);
    T->add_Node(3);

    CallGenerator CG(T, 100);

    //Network load setting
    CG.set_Load(200);
    EXPECT_EQ(CG.h, 200) << "Network load is not being set.";
}

TEST(CallGeneratorTest, CallGeneration)
{
    //Setting up
    std::shared_ptr<Topology> T = std::make_shared<Topology>();
    T->add_Node(1);
    T->add_Node(2);
    T->add_Node(3);
    CallGenerator CG(T, 100);

    //Call generation
    std::shared_ptr<Call> Call1 = CG.generate_Call();
    std::shared_ptr<Call> Call2 = CG.generate_Call();
    std::shared_ptr<Call> Call3 = CG.generate_Call();

    //Tests whether the generated events make sense
    EXPECT_LT(*(Call1->CallRequisition.lock()), *(Call1->CallEnding.lock())) << "Any call should end after it starts.";
    EXPECT_LT(*(Call2->CallRequisition.lock()), *(Call2->CallEnding.lock())) << "Any call should end after it starts.";
    EXPECT_LT(*(Call3->CallRequisition.lock()), *(Call3->CallEnding.lock())) << "Any call should end after it starts.";
    EXPECT_LT(*(Call1->CallRequisition.lock()), *(Call2->CallRequisition.lock())) << "Any call should start before the succeeding call.";
    EXPECT_LT(*(Call2->CallRequisition.lock()), *(Call3->CallRequisition.lock())) << "Any call should start before the succeeding call.";

    //Tests whether the events are being correctly being saved into the priority queue
    EXPECT_EQ(CG.Events.size(), 6) << "There should be two events per generated call.";
    EXPECT_EQ(*(Call1->CallRequisition.lock()), *(CG.Events.top())) << "The first event should be the beginning of the first call";
}

#endif
