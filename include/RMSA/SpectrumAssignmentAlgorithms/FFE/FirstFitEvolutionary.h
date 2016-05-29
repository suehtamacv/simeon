#ifndef FIRSTFITEVOLUTIONARY_H
#define FIRSTFITEVOLUTIONARY_H

#include "../SpectrumAssignmentAlgorithm.h"

namespace RMSA
{
namespace SA
{
namespace FFE
{
class FirstFitEvolutionary : public SpectrumAssignmentAlgorithm
{
public:
    FirstFitEvolutionary(std::shared_ptr<Topology> T);

    void load();
    void save(std::string);
    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>>
        assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);

    void setSlotsList(std::vector<int> newSlotsList);
    static void setDefaultSlotsList(std::vector<int> newSlotsList);

private:
    static bool hasLoaded;
    bool hasSetSlots;
    static std::vector<int> defaultSlotsList;

    static bool initDefaultList(std::string);

    std::vector<int> slotsList;
};
}
}
}

#endif // FIRSTFITEVOLUTIONARY_H
