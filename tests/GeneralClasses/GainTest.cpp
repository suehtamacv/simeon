#include <gtest/gtest.h>
#include "GeneralClasses/Gain.h"

TEST(GainTest, Constructors)
{
    Gain G1(123);
    Gain G2(G1);

    EXPECT_EQ(G1, G2) << "Copy constructor not working as expected.";
}

TEST(GainTest, Conversions)
{
    Gain G1(0);
    Gain G2(0, Gain::dB);
    Gain G3(1, Gain::Linear);
    Gain G4(1, Gain::dB);
    Gain G5(10, Gain::dB);

    EXPECT_EQ(G1, G2) << "Gains should be, by default, specified in dB.";

    EXPECT_EQ(G1, G3) << "Conversion from dB to linear units failed.";
    EXPECT_EQ(G1.in_dB(), G3.in_dB()) << "Conversion from dB to linear units failed.";
    EXPECT_EQ(G1.in_Linear(), G3.in_Linear()) << "Conversion from dB to linear units failed.";

    EXPECT_NE(G3, G4) << "Conversion between dB and linear units not working as expected.";

    EXPECT_GT(G5.in_Linear(), 1) << "A gain of " << G5 << "should be greater than 1.";
}

TEST(GainTest, BasicOperations)
{
    Gain G1(0);
    Gain G2(0);

    //Summing and subtracting gains
    EXPECT_EQ(G1 + G1, G1) << G1 << " + " << G1 << "should be equal to " << G1 << ".";
    EXPECT_EQ(G1 + G2, G1) << G1 << " + " << G2 << "should be equal to " << G1 << ".";
    EXPECT_EQ(G1 - G1, G1) << G1 << " - " << G1 << "should be equal to " << G1 << ".";
    EXPECT_EQ(G1 - G2, G1) << G1 << " - " << G2 << "should be equal to " << G1 << ".";

    //Assignments
    G1 = G1 + G1;
    EXPECT_EQ(G1, G2) << G1 << " + " << G1 << "should be equal to " << G2 << ".";
    G2 = G2 - G2;
    EXPECT_EQ(G1, G2) << G2 << " - " << G2 << "should be equal to " << G1 << ".";

    //Symmetrical gains
    Gain G3(1, Gain::Linear);
    EXPECT_EQ(G3, -G3) << "A gain of 1 should be equal to a gain of 1/1.";

    Gain G4(10);
    EXPECT_LE(G1, G4) << "A gain of " << G1 << " should be less than or equal to a gain of " << G4 << ".";
    EXPECT_LT(G1, G4) << "A gain of " << G1 << " should be less than a gain of " << G4 << ".";
    EXPECT_GE(G1, -G4) << "A gain of " << G1 << " should be greater than or equal to a gain of " << -G4 << ".";
    EXPECT_GT(G1, -G4) << "A gain of " << G1 << " should be greater than a gain of " << -G4 << ".";

    EXPECT_LT((-G4).in_Linear(), 1) << "A gain of " << -G4 << " should be greater than 1.";
}
