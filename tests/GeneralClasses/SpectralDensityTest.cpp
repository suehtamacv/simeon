#ifdef RUN_TESTS

#include <gtest/gtest.h>
#include <GeneralClasses/SpectralDensity.h>

TEST(SpectralDensityTest, Constructors)
{
    double centerFreq = 193.4E12;
    double freqRange = 25E9;
    unsigned int numSamples = 100;

    SpectralDensity cleanSpecDens(centerFreq - freqRange, centerFreq + freqRange, numSamples, true);
    for(auto& val : cleanSpecDens.specDensity)
        {
        EXPECT_EQ(val, 0) << "Clean spectral density constructor not working.";
        }

    SpectralDensity specDens(centerFreq - freqRange, centerFreq + freqRange, numSamples, false);
    EXPECT_EQ(specDens.densityScaling, Gain(0,
                                            Gain::dB)) << "The proper density scaling is not being initialized.";
    EXPECT_EQ(specDens.freqMin, centerFreq - freqRange) <<
            "The proper minimum frequency is not being initialized.";
    EXPECT_EQ(specDens.freqMax, centerFreq + freqRange) <<
            "The proper maximum frequency is not being initialized.";
    EXPECT_EQ(specDens.stepFrequency,
              freqRange * 2 / (double) numSamples) << "The proper step frequency is not being initialized.";
    EXPECT_EQ(specDens.specDensity.n_cols,
              numSamples) << "The proper number of samples is not being initialized.";
    EXPECT_GT((specDens.specDensity)(numSamples / 2), (specDens.specDensity)(0)) <<
            "Gaussian function exhibiting irregular behavior.";
    EXPECT_GT((specDens.specDensity)(numSamples / 2), (specDens.specDensity)(numSamples - 1)) <<
            "Gaussian function exhibiting irregular behavior.";

    SpectralDensity specDens2(specDens);
    EXPECT_EQ(specDens, specDens2) << "Copy constructor not working as expected.";
}

#endif
