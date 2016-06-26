#ifdef RUN_TESTS

#include <gtest/gtest.h>
#include <GeneralClasses/Transmittances/Transmittance.h>
#include <GeneralClasses/Transmittances/ConstantTransmittance.h>
#include <GeneralClasses/Transmittances/GaussianFilter.h>
#include <GeneralClasses/Transmittances/GaussianPassbandFilter.h>
#include <GeneralClasses/Transmittances/GaussianStopbandFilter.h>

#include <Devices/SSS.h>

using namespace TF;

TEST(TransmittanceTest, ConstantTransmittanceTest)
{
    unsigned int NumPorts = 4;
    Gain TempSplitterGain (1.0 / (NumPorts + 1), Gain::Linear);
    ConstantTransmittance ConstTransmit(TempSplitterGain);

    EXPECT_EQ(ConstTransmit.get_Gain(),
              TempSplitterGain) << "The proper gain is not being initialized.";

    double freqValue1 = 193.4E12;
    double freqValue2 = 193.4E12 + 25E9;
    EXPECT_EQ(ConstTransmit.get_TransmittanceAt(freqValue1),
              ConstTransmit.get_TransmittanceAt(freqValue2)) <<
                      "The frequency is being considered in the constant transmittance.";
}

TEST(TransmittanceTest, GaussianPassbandFilterTest)
{
    constexpr static double centerFreq = 193.4E12;
    unsigned int filterOrder = 1;
    GaussianPassbandFilter GaussPBFilter(centerFreq, filterOrder, Devices::SSS::SSSLoss);

    EXPECT_EQ(GaussPBFilter.get_CenterFreq(),
              centerFreq) << "The proper frequency is not being initialized.";
    EXPECT_EQ(GaussPBFilter.get_FilterOrder(),
              filterOrder) << "The proper filter order is not being initialized.";
    EXPECT_EQ(GaussPBFilter.get_Gain(), Devices::SSS::SSSLoss)
            << "The proper gain is not being initialized.";

    double freqRange = 25E9;
    EXPECT_LT(GaussPBFilter.get_TransmittanceAt(GaussPBFilter.get_CenterFreq() - freqRange),
              GaussPBFilter.get_TransmittanceAt(GaussPBFilter.get_CenterFreq())) <<
                      "Gaussian passband filter function exhibiting irregular behavior.";
    EXPECT_LT(GaussPBFilter.get_TransmittanceAt(GaussPBFilter.get_CenterFreq() + freqRange),
              GaussPBFilter.get_TransmittanceAt(GaussPBFilter.get_CenterFreq())) <<
                      "Gaussian passband filter function exhibiting irregular behavior.";

    GaussianStopbandFilter GaussSBFilter(centerFreq, filterOrder, Devices::SSS::SSSLoss);
    Gain GPBGain = GaussPBFilter.get_TransmittanceAt(centerFreq) - GaussPBFilter.get_Gain();
    Gain GSBGain = GaussSBFilter.get_TransmittanceAt(centerFreq) - GaussSBFilter.get_Gain();
    EXPECT_EQ(GPBGain.in_Linear(),
              1 - GSBGain.in_Linear()) <<
                      "Gaussian Passband function not complementary to Gaussian Stopband function.";
}

TEST(TransmittanceTest, GaussianStopbandFilterTest)
{
    constexpr static double centerFreq = 193.4E12;
    unsigned int filterOrder = 1;
    GaussianStopbandFilter GaussSBFilter(centerFreq, filterOrder, Devices::SSS::SSSLoss);

    EXPECT_EQ(GaussSBFilter.get_CenterFreq(),
              centerFreq) << "The proper frequency is not being initialized.";
    EXPECT_EQ(GaussSBFilter.get_FilterOrder(),
              filterOrder) << "The proper filter order is not being initialized.";
    EXPECT_EQ(GaussSBFilter.get_Gain(), Devices::SSS::SSSLoss)
            << "The proper gain is not being initialized.";

    double freqRange = 25E9;
    EXPECT_GT(GaussSBFilter.get_TransmittanceAt(GaussSBFilter.get_CenterFreq() - freqRange),
              GaussSBFilter.get_TransmittanceAt(GaussSBFilter.get_CenterFreq())) <<
                      "Gaussian stopband filter function exhibiting irregular behavior.";
    EXPECT_GT(GaussSBFilter.get_TransmittanceAt(GaussSBFilter.get_CenterFreq() + freqRange),
              GaussSBFilter.get_TransmittanceAt(GaussSBFilter.get_CenterFreq())) <<
                      "Gaussian stopband filter function exhibiting irregular behavior.";

    GaussianPassbandFilter GaussPBFilter(centerFreq, filterOrder, Devices::SSS::SSSLoss);
    Gain GPBGain = GaussPBFilter.get_TransmittanceAt(centerFreq) - GaussPBFilter.get_Gain();
    Gain GSBGain = GaussSBFilter.get_TransmittanceAt(centerFreq) - GaussSBFilter.get_Gain();
    EXPECT_EQ(GPBGain.in_Linear(),
              1 - GSBGain.in_Linear()) <<
                      "Gaussian Stopband function not complementary to Gaussian Passband function.";
}

#endif
