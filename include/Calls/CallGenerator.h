#ifndef CALLGENERATOR_H
#define CALLGENERATOR_H

#include <queue>
#include <Calls/Event.h>

class CallGenerator {
  public:
    CallGenerator();

    std::priority_queue<Event> Events;
};

#endif // CALLGENERATOR_H
