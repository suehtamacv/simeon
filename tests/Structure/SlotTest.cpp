#ifdef RUN_TESTS

#include "Structure/Slot.h"
#include <gtest/gtest.h>

TEST(SlotTest, Constructor)
{
    Slot S1(1);
    EXPECT_TRUE(S1.isFree) << "Slot should start as free.";

    Slot S2(S1);
    EXPECT_TRUE(S2.isFree) << "Slot should start as free.";
    EXPECT_EQ(S1.numSlot, S2.numSlot) << "Copy constructor not working as it should.";
    EXPECT_EQ(S1.isFree, S2.isFree) << "Copy constructor not working as it should.";

    Slot S3 = S1;
    EXPECT_TRUE(S3.isFree) << "Slot should start as free.";
    EXPECT_EQ(S1.numSlot, S3.numSlot) << "Assignment operator not working as it should.";
    EXPECT_EQ(S1.isFree, S3.isFree) << "Assignment operator not working as it should.";
}

TEST(SlotTest, Operations)
{
    Slot S1(1);
    Slot S2(S1);

    S1.useSlot();
    EXPECT_FALSE(S1.isFree) << "Slot should be occupied.";
    EXPECT_TRUE(S2.isFree) << "Slot should be free.";

    S1.freeSlot();
    EXPECT_TRUE(S1.isFree) << "Slot should be free.";
    EXPECT_TRUE(S2.isFree) << "Slot should be free.";
}

#endif
