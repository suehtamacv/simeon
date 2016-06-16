#ifdef RUN_TESTS

#include "include/Structure.h"
#include "include/RMSA/TransparentSegment.h"
#include <gtest/gtest.h>

extern bool considerFilterImperfection;

TEST(CrosstalkTest, Epsilon)
{
    considerFilterImperfection = true;

    std::shared_ptr<Topology> T = std::make_shared<Topology>();
    std::shared_ptr<Node> N1 = T->add_Node(1).lock();
    std::shared_ptr<Node> N2 = T->add_Node(2).lock();
    std::shared_ptr<Node> N3 = T->add_Node(3).lock();
    std::shared_ptr<Node> N4 = T->add_Node(4).lock();
    std::shared_ptr<Link> L14 = T->add_Link(N1, N4, 1000).lock();
    std::shared_ptr<Link> L24 = T->add_Link(N2, N4, 1000).lock();
    std::shared_ptr<Link> L34 = T->add_Link(N3, N4, 1000).lock();

    mapSlots sl14, sl24, sl34;
    sl14[L14] = {L14->Slots[0], L14->Slots[1], L14->Slots[2], L14->Slots[3]};
    sl24[L24] = {L24->Slots[1], L24->Slots[2]};
    sl34[L34] = {L34->Slots[2], L34->Slots[3]};

    RMSA::TransparentSegment Seg14({L14}, ModulationScheme(4, Gain(6.8)), 0);
    RMSA::TransparentSegment Seg24({L24}, ModulationScheme(4, Gain(6.8)), 0);
    RMSA::TransparentSegment Seg34({L34}, ModulationScheme(4, Gain(6.8)), 0);

    Signal S14(sl14);
    Signal S24(sl24);
    Signal S34(sl34);

    S24 = Seg24.bypass(S24);
    S34 = Seg34.bypass(S34);
    L24->linkSpecDens->updateLink(Seg24.opticalPathSpecDensity.front(), sl24.begin()->second);
    L34->linkSpecDens->updateLink(Seg34.opticalPathSpecDensity.front(), sl34.begin()->second);

    for (auto &slot : sl24.begin()->second)
        {
        slot.lock()->useSlot();
        }
    for (auto &slot : sl34.begin()->second)
        {
        slot.lock()->useSlot();
        }

    S14 = Seg14.bypass(S14);
    std::cout << S14.get_WeightedCrosstalk() << std::endl;
}

#endif
