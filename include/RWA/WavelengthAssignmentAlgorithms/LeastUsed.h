#ifndef LEASTUSED_H
#define LEASTUSED_H

#include "WavelengthAssignmentAlgorithm.h"

class LeastUsed : public WavelengthAssignmentAlgorithm
{
public:
    LeastUsed(std::shared_ptr<Topology> T);

    std::map<std::weak_ptr<Link>,
        std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>>
        assignSlots(std::shared_ptr<Call> C, TransparentSegment Seg);
    void load() {}
    void save(std::string);
};

#endif // LEASTUSED_H
