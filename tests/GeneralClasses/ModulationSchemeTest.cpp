#include "include/GeneralClasses/ModulationScheme.h"
#include <gtest/gtest.h>

TEST(ModulationSchemeTest, Constructors)
{
    Gain G(10);
    ModulationScheme M1(4, G);
    EXPECT_EQ(M1.get_SNR_Per_Bit(), G) << "SNR Per Bit not being correctly set.";

    ModulationScheme M2(M1);
    ModulationScheme M3 = M1;

    EXPECT_EQ(M1, M2) << "Copy constructor not working as it should.";
    EXPECT_EQ(M1.get_SNR_Per_Bit(), M2.get_SNR_Per_Bit()) << "Copy constructor not working as it should.";
    EXPECT_EQ(M1.get_M(), M2.get_M()) << "Copy constructor not working as it should.";

    EXPECT_EQ(M1, M3) << "Assignment operator not working as it should.";
    EXPECT_EQ(M1.get_SNR_Per_Bit(), M3.get_SNR_Per_Bit()) << "Assignment operator not working as it should.";
    EXPECT_EQ(M1.get_M(), M3.get_M()) << "Assignment operator not working as it should.";
}

TEST(ModulationSchemeTest, Operations)
{
    ModulationScheme M1(4, Gain(15));
    ModulationScheme M2(4, Gain(15));
    ModulationScheme M3(16, Gain(20));

    EXPECT_EQ(M1, M2) << M1 << " should be equal to " << M2 << ".";
    EXPECT_NE(M1, M3) << M1 << " should not be equal to " << M3 << ".";
    EXPECT_LT(M1, M3) << M1 << " should be less than to " << M3 << ".";
    EXPECT_LE(M1, M3) << M1 << " should be less than or equal to " << M3 << ".";
    EXPECT_GT(M3, M2) << M3 << " should be greater than to " << M2 << ".";
    EXPECT_GE(M3, M2) << M3 << " should be greater than or equal to " << M2 << ".";
}
