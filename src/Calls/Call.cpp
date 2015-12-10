#include <Calls/Call.h>

Call::Call(long double tOcurr, long double tDur, std::weak_ptr<Node> Origin,
           std::weak_ptr<Node> Destination, TransmissionBitrate Bitrate)  :
    Origin(Origin),
    Destination(Destination),
    Bitrate(Bitrate) {

    CallRequisition = std::shared_ptr<Event>(
                          new Event(tOcurr, Event::CallRequisition, this));
    CallEnding = std::shared_ptr<Event>(
                     new Event(tOcurr + tDur, Event::CallEnding, this));
}
