#include <Calls/Call.h>

Call::Call(long double tOcurr, long double tDur, std::weak_ptr<Node> Origin,
           std::weak_ptr<Node> Destination, TransmissionBitrate Bitrate)  :
    CallRequisition(tOcurr, Event::CallRequisition, std::shared_ptr<Call>(this)),
    CallEnding(tOcurr + tDur, Event::CallEnding, std::shared_ptr<Call>(this)),
    Origin(Origin),
    Destination(Destination),
    Bitrate(Bitrate) {

}
