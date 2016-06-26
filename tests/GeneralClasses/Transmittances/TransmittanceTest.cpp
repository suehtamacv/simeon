#ifdef RUN_TESTS

#include <gtest/gtest.h>
#include <GeneralClasses/Transmittances/Transmittance.h>
#include <GeneralClasses/Transmittances/ConstantTransmittance.h>
#include <GeneralClasses/Transmittances/GaussianFilter.h>
#include <GeneralClasses/Transmittances/GaussianPassbandFilter.h>
#include <GeneralClasses/Transmittances/GaussianStopbandFilter.h>

using namespace TF;

TEST(TransmittanceTest, ConstantTransmittanceTest)
{
    Gain G(321);
    ConstantTransmittance ConstTransmit(G);

    EXPECT_EQ(ConstTransmit.get_Gain(), G) << "The proper gain is not being initialized.";

    double freqValue1 = 12234;
    double freqValue2 = 15341;
    EXPECT_EQ(ConstTransmit.get_TransmittanceAt(freqValue1), ConstTransmit.get_TransmittanceAt(freqValue2)) <<
            "The frequency is being considered in the constant transmittance.";
}

TEST(TransmittanceTest, GaussianPassbandFilterTest)
{
    double centerFreq = 193.4E12;
    unsigned int filterOrder = 3;
    Gain G(0.541);
    GaussianPassbandFilter GaussPBFilter(centerFreq, filterOrder, G);

    EXPECT_EQ(GaussPBFilter.get_CenterFreq(), centerFreq) <<
            "The proper frequency is not being initialized.";
    EXPECT_EQ(GaussPBFilter.get_FilterOrder(), filterOrder) <<
            "The proper filter order is not being initialized.";
    EXPECT_EQ(GaussPBFilter.get_Gain(), G) << "The proper gain is not being initialized.";

    double freqRange = 25E9;
    EXPECT_LT(GaussPBFilter.get_TransmittanceAt(GaussPBFilter.get_CenterFreq() - freqRange),
              GaussPBFilter.get_TransmittanceAt(GaussPBFilter.get_CenterFreq())) <<
                      "Gaussian passband filter function exhibiting irregular behavior.";
    EXPECT_LT(GaussPBFilter.get_TransmittanceAt(GaussPBFilter.get_CenterFreq() + freqRange),
              GaussPBFilter.get_TransmittanceAt(GaussPBFilter.get_CenterFreq())) <<
                      "Gaussian passband filter function exhibiting irregular behavior.";
}

TEST(TransmittanceTest, GaussianStopbandFilterTest)
{
    double centerFreq = 193.4E12;
    unsigned int filterOrder = 3;
    Gain G(0.541);
    GaussianStopbandFilter GaussSBFilter(centerFreq, filterOrder, G);

    EXPECT_EQ(GaussSBFilter.get_CenterFreq(), centerFreq) <<
            "The proper frequency is not being initialized.";
    EXPECT_EQ(GaussSBFilter.get_FilterOrder(), filterOrder) <<
            "The proper filter order is not being initialized.";
    EXPECT_EQ(GaussSBFilter.get_Gain(), G) << "The proper gain is not being initialized.";

    double freqRange = 25E9;
    EXPECT_GT(GaussSBFilter.get_TransmittanceAt(GaussSBFilter.get_CenterFreq() - freqRange),
              GaussSBFilter.get_TransmittanceAt(GaussSBFilter.get_CenterFreq())) <<
                      "Gaussian stopband filter function exhibiting irregular behavior.";
    EXPECT_GT(GaussSBFilter.get_TransmittanceAt(GaussSBFilter.get_CenterFreq() + freqRange),
              GaussSBFilter.get_TransmittanceAt(GaussSBFilter.get_CenterFreq())) <<
                      "Gaussian stopband filter function exhibiting irregular behavior.";
}

#endif
