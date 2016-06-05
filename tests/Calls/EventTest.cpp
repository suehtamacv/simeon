#ifdef RUN_TESTS

#include "Calls/Event.h"
#include <gtest/gtest.h>

TEST(EventTest, Constructor)
{
    Event evt1(0.1, Event::CallRequisition, nullptr);
    EXPECT_EQ(evt1.t, 0.1) << "Constructor not working as it should.";
    EXPECT_EQ(evt1.Type, Event::CallRequisition) << "Constructor not working as it should.";
    EXPECT_EQ(evt1.Parent, nullptr) << "Constructor not working as it should.";

    Event evt2(0.2, Event::CallEnding, nullptr);
    EXPECT_EQ(evt2.t, 0.2) << "Constructor not working as it should.";
    EXPECT_EQ(evt2.Type, Event::CallEnding) << "Constructor not working as it should.";
    EXPECT_EQ(evt2.Parent, nullptr) << "Constructor not working as it should.";
}

TEST(EventTest, Comparison)
{
    Event evt1(0.1, Event::CallRequisition, nullptr);
    Event evt2(0.2, Event::CallRequisition, nullptr);
    Event evt3(0.3, Event::CallEnding, nullptr);

    EXPECT_LT(evt1, evt2) << "Events should be ordered by their occurral times.";
    EXPECT_LT(evt1, evt3) << "Events should be ordered by their occurral times.";
    EXPECT_LT(evt2, evt3) << "Events should be ordered by their occurral times.";
    EXPECT_GT(evt2, evt1) << "Events should be ordered by their occurral times.";
    EXPECT_GT(evt3, evt1) << "Events should be ordered by their occurral times.";
    EXPECT_GT(evt3, evt2) << "Events should be ordered by their occurral times.";
}

#endif
