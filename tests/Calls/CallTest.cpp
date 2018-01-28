#ifdef RUN_TESTS

#include "include/Calls/Call.h"
#include "include/Structure/Node.h"
#include <gtest/gtest.h>

TEST(CallTest, Constructor)
{
    //Setting up
    std::shared_ptr<Node> N1 = std::make_shared<Node>(1);
    std::shared_ptr<Node> N2 = std::make_shared<Node>(2);
    TransmissionBitrate BR(100E9);

    //Testing
    std::shared_ptr<Call> C = std::make_shared<Call>(N1, N2, BR);
    EXPECT_EQ(*(C->Origin.lock()), *N1) << "Source node not being correctly set.";
    EXPECT_EQ(*(C->Destination.lock()), *N2) << "Destination node not being correctly set.";
    EXPECT_EQ(C->Bitrate, BR) << "Bitrate being correctly set.";
    EXPECT_EQ(C->Status, Call::Not_Evaluated) << "A call should start as non-evaluated.";
}

#endif
