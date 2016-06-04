#include <gtest/gtest.h>
#include "GeneralClasses/Power.h"

TEST(PowerTest, Constructors)
{
    Power P1(123);
    Power P2(P1);

    EXPECT_EQ(P1, P2) << "Copy constructor not working as expected.";
}

TEST(PowerTest, Conversions)
{
    Power P1(0);
    Power P2(0, Power::dBm);
    Power P3(0.001L, Power::Watt);
    Power P4(0.001L, Power::dBm);
    Power P5(10, Power::dBm);

    EXPECT_EQ(P1, P2) << "Powers should be, by default, specified in dBm.";

    EXPECT_EQ(P1, P3) << "Conversion from dBm to Watts failed.";
    EXPECT_EQ(P1.in_dBm(), P3.in_dBm()) << "Conversion from dBm to Watts failed.";
    EXPECT_EQ(P1.in_Watts(), P3.in_Watts()) << "Conversion from dBm to Watts failed.";

    EXPECT_NE(P3, P4) << "Conversion between dBm and Watts not working as expected.";

    EXPECT_GT(P5.in_Watts(), 0.001L) << "A power of " << P5 << "should be greater than 0.001 mW.";
}

TEST(PowerTest, BasicOperations)
{
    Power P1(10, Power::dBm); //10dBm = 0.01W
    Power P2(0.01L, Power::Watt);
    Power P3(0.02L, Power::Watt);

    //Comparisons
    EXPECT_LE(P1, P3) << "A power of " << P1 << " should be less than or equal to " << P3 << ".";
    EXPECT_LT(P1, P3) << "A power of " << P1 << " should be less than " << P3 << ".";
    EXPECT_LE(P2, P3) << "A power of " << P2 << " should be less than or equal to " << P3 << ".";
    EXPECT_LT(P2, P3) << "A power of " << P2 << " should be less than " << P3 << ".";
    EXPECT_GE(P3, P1) << "A power of " << P3 << " should be greater than or equal to " << P1 << ".";
    EXPECT_GT(P3, P2) << "A power of " << P3 << " should be greater than " << P2 << ".";

    //Arithmetic
    EXPECT_EQ(P1 + P1, P3) << P1 << " + " << P1 << " should be equal to " << P3 << ".";
    EXPECT_EQ(P1 + P2, P3) << P1 << " + " << P2 << " should be equal to " << P3 << ".";
    EXPECT_EQ(P2 + P2, P3) << P2 << " + " << P2 << " should be equal to " << P3 << ".";
}

TEST(PowerTest, OperationsWithGains)
{
    Gain G1(1, Gain::Linear);
    Power P1(123);
    EXPECT_EQ(P1, P1 * G1) << "A gain of " << G1 << " should not affect the power.";

    Power P2(10, Power::dBm);
    Power P3(20, Power::dBm);
    Gain G2(50, Gain::dB);
    Gain G3(50, Gain::Linear);
    Gain G4 = P2 / P3;

    //10dBm + 50dB = 60dBm
    EXPECT_EQ(P2 * G2, Power(60)) << "A power of " << P2 << " subjected to a gain of " << G2 << " should be equal to a power of " << Power(60) << ".";
    //10dBm + 50(linear) != 60dBm
    EXPECT_NE(P2 * G3, Power(60)) << "A power of " << P2 << " subjected to a gain of " << G3 << " should not be equal to a power of " << Power(60) << ".";
    //10dBm / 20dBm = -10dB
    EXPECT_EQ(G4, Gain(-10)) << "A power of " << P2 << " over a power of " << P3 << " should be equal to a gain of " << Gain(-10) << ".";
    //20dBm + (-10dB) = 10dBm
    EXPECT_EQ(P3 * G4, P2) << "A power of " << P3 << " times a gain of " << G4 << " should be equal to " << P2 << ".";
}
