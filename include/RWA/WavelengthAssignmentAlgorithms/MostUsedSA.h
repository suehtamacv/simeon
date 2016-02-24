#ifndef MOSTUSED_H
#define MOSTUSED_H

#include "WavelengthAssignmentAlgorithm.h"

namespace WA
{
class MostUsed : public WavelengthAssignmentAlgorithm
{
public:
    MostUsed(std::shared_ptr<Topology> T);

    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>>
        assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);
    void load() {}
    void save(std::string);
};
}

#endif // MOSTUSED_H
