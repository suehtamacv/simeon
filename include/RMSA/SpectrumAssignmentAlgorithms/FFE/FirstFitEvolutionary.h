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

    void load() {}
    void save(std::string);
    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>>
        assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);

private:
    static bool hasLoaded;
    static bool hasCreatedDefaultList;
    static std::vector<int> defaultSlotsList;

    std::vector<int> slotsList;
};
}
}
}

#endif // FIRSTFITEVOLUTIONARY_H
