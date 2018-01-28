#ifdef RUN_TESTS

#include "include/Devices/Fiber.h"
#include <gtest/gtest.h>

TEST(DevicesTest, FiberTest)
{
    Devices::Fiber Fiber1(200);
    EXPECT_EQ(Fiber1.get_TransferFunction(1000)->get_TransmittanceAt(123), Fiber1.get_Gain()) << "Transfer function gain not being correctly set.";

    Devices::Fiber Fiber2(100);
    EXPECT_NE(Fiber1.get_Gain(), Fiber2.get_Gain()) << "Fiber loss not being correctly set.";
    EXPECT_EQ(Fiber1.get_Gain().in_dB(), 2 * Fiber2.get_Gain().in_dB()) << "Fiber gain should scale linearly.";

    std::shared_ptr<Devices::Device> Fiber3 = Fiber1.clone();
    EXPECT_EQ(Fiber1.get_Gain(), Fiber3->get_Gain()) << "Fiber cloning not working correctly: gain unequal.";
    EXPECT_EQ(Fiber1.get_Noise(), Fiber3->get_Noise()) << "Fiber cloning not working correctly: noise unequal.";
    EXPECT_EQ(Fiber1.get_CapEx(), Fiber3->get_CapEx()) << "Fiber cloning not working correctly: CapEx unequal.";
    EXPECT_EQ(Fiber1.get_OpEx(), Fiber3->get_OpEx()) << "Fiber cloning not working correctly: OpEx unequal.";
}

#endif
