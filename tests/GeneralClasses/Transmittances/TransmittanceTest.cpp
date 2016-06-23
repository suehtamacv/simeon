#ifdef RUN_TESTS

#include <gtest/gtest.h>
#include <GeneralClasses/Transmittances/Transmittance.h>
#include <GeneralClasses/Transmittances/ConstantTransmittance.h>
#include <GeneralClasses/Transmittances/GaussianFilter.h>
#include <GeneralClasses/Transmittances/GaussianPassbandFilter.h>
#include <GeneralClasses/Transmittances/GaussianStopbandFilter.h>

#include <Devices/SSS.h>

using namespace TF;

TEST(TransmittanceTest, GaussianPassbandFilterTest)
{
    constexpr static double centerFreq = 193.4E12;
    unsigned int filterOrder = 1;
    GaussianPassbandFilter GaussPBFilter(centerFreq, filterOrder, Devices::SSS::SSSLoss);

    EXPECT_EQ(GaussPBFilter.get_CenterFreq(),
              centerFreq) << "Gaussian Passband Filter not initializing the proper center frequencie.";
    EXPECT_EQ(GaussPBFilter.get_FilterOrder(),
              filterOrder) << "Gaussian Passband Filter not initializing the proper filter order.";
    EXPECT_EQ(GaussPBFilter.get_Gain(), Devices::SSS::SSSLoss)
            << "Gaussian Passband Filter not initializing the proper gain.";
}

#endif
