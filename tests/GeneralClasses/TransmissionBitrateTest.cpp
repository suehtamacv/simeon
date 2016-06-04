#include "include/GeneralClasses/TransmissionBitrate.h"
#include <gtest/gtest.h>

TEST(TransmissionBitrateTest, Constructors)
{
    TransmissionBitrate BR1(25E9);
    TransmissionBitrate BR2(BR1);

    EXPECT_EQ(BR1, BR2) << "Copy constructor not working as it should.";
}

TEST(TransmissionBitrateTest, Operations)
{
    TransmissionBitrate BR1(10E9);
    TransmissionBitrate BR2(10E9);
    TransmissionBitrate BR3(100E9);

    EXPECT_EQ(BR1, BR2) << "A bitrate of " << BR1 << " should be equal to a bitrate of " << BR2 << ".";
    EXPECT_NE(BR1, BR3) << "A bitrate of " << BR1 << " should not be equal to a bitrate of " << BR3 << ".";

    EXPECT_LT(BR1, BR3) << "A bitrate of " << BR1 << " should be less than a bitrate of " << BR3 << ".";
    EXPECT_LE(BR1, BR3) << "A bitrate of " << BR1 << " should be less than or equal to a bitrate of " << BR3 << ".";
    EXPECT_GT(BR3, BR1) << "A bitrate of " << BR3 << " should be greater than a bitrate of " << BR1 << ".";
    EXPECT_GE(BR3, BR1) << "A bitrate of " << BR3 << " should be greater than or equal to a bitrate of " << BR1 << ".";
}
