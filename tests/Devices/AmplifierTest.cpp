#ifdef RUN_TESTS

#include "include/Devices/Amplifiers.h"
#include "include/Devices/Fiber.h"
#include "include/Devices/SSS.h"
#include "include/Structure.h"
#include <gtest/gtest.h>

using namespace Devices;

TEST(DevicesTest, BoosterAmplifierTest)
{
    BoosterAmplifier BoosterAmp;
    EXPECT_EQ((int) BoosterAmp.AT, Amplifier::BoosterAmplifierType) << "Booster amplifier not being identified as one.";

    std::shared_ptr<Device> BoosterAmpClone = BoosterAmp.clone();
    EXPECT_EQ(BoosterAmp.get_Gain(), BoosterAmpClone->get_Gain()) << "Booster amplifier cloning not working.";
    EXPECT_EQ(BoosterAmp.get_Noise(), BoosterAmpClone->get_Noise()) << "Booster amplifier cloning not working.";
    EXPECT_EQ(BoosterAmp.get_CapEx(), BoosterAmpClone->get_CapEx()) << "Booster amplifier cloning not working.";
    EXPECT_EQ(BoosterAmp.get_OpEx(), BoosterAmpClone->get_OpEx()) << "Booster amplifier cloning not working.";
}

TEST(DevicesTest, InLineAmplifierTest)
{
    Fiber fiberSegment(200);
    InLineAmplifier InLineAmp(fiberSegment);
    EXPECT_EQ((int) InLineAmp.AT, Amplifier::InLineAmplifierType) << "In-line amplifier not being identified as one.";
    EXPECT_EQ(InLineAmp.get_Gain(), -fiberSegment.get_Gain()) << "The In-line amplifier should compensate for the losses on the previous fiber segment.";

    std::shared_ptr<Device> InLineAmpClone = InLineAmp.clone();

    EXPECT_EQ(InLineAmp.get_Gain(), InLineAmpClone->get_Gain()) << "In-line amplifier cloning not working as expected.";
    EXPECT_EQ(InLineAmp.get_Noise(), InLineAmpClone->get_Noise()) << "In-line amplifier cloning not working as expected.";
    EXPECT_EQ(InLineAmp.get_CapEx(), InLineAmpClone->get_CapEx()) << "In-line amplifier cloning not working as expected.";
    EXPECT_EQ(InLineAmp.get_OpEx(), InLineAmpClone->get_OpEx()) << "In-line amplifier cloning not working as expected.";
}

TEST(DevicesTest, PreAmplifierTest)
{
    Fiber fiberSegment(325);
    Node N(1, Node::TransparentNode, Node::SwitchingSelect);
    PreAmplifier PreAmp(fiberSegment, N);

    EXPECT_EQ((int) PreAmp.AT, Amplifier::PreAmplifierType) << "Preamplifier not being identified as one.";
    EXPECT_EQ(PreAmp.get_Gain(), -fiberSegment.get_Gain() - SSS::SSSLoss) << "A preamplifier should compensate for the losses on the previous fiber segment and the losses on the following SSS device (if SS Node Architecture) or Splitter device (if BS Node Architecture).";

    std::shared_ptr<Device> PreAmpClone = PreAmp.clone();

    EXPECT_EQ(PreAmp.get_Gain(), PreAmpClone->get_Gain()) << "Preamplifier cloning not working as expected.";
    EXPECT_EQ(PreAmp.get_Noise(), PreAmpClone->get_Noise()) << "Preamplifier cloning not working as expected.";
    EXPECT_EQ(PreAmp.get_CapEx(), PreAmpClone->get_CapEx()) << "Preamplifier cloning not working as expected.";
    EXPECT_EQ(PreAmp.get_OpEx(), PreAmpClone->get_OpEx()) << "Preamplifier cloning not working as expected.";
}

#endif
