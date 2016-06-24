#ifdef RUN_TESTS

#include <gtest/gtest.h>
#include <GeneralClasses/Transmittances/Transmittance.h>
#include <GeneralClasses/Transmittances/ConstantTransmittance.h>
#include <GeneralClasses/Transmittances/GaussianFilter.h>
#include <GeneralClasses/Transmittances/GaussianPassbandFilter.h>
#include <GeneralClasses/Transmittances/GaussianStopbandFilter.h>

#include <Devices/SSS.h>
#include <cstdlib>

using namespace TF;

TEST(TransmittanceTest, ConstantTransmittanceTest)
{
    unsigned int NumPorts = 4;
    Gain TempSplitterGain (1.0 / (NumPorts + 1), Gain::Linear);
    ConstantTransmittance ConstTransmit(TempSplitterGain);

    EXPECT_EQ(ConstTransmit.get_Gain(),
              TempSplitterGain) << "The proper gain is not being initialized.";

    double freqValue1 = 1.0 * rand();
    double freqValue2 = 1.0 * rand();
    EXPECT_EQ(ConstTransmit.get_TransmittanceAt(freqValue1),
              ConstTransmit.get_TransmittanceAt(freqValue2)) <<
                      "The frequency is being considered in the transmittance.";
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
}

#endif
