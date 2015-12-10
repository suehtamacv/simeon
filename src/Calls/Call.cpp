#include <Calls/Call.h>

Call::Call(long double tOcurr, long double tDur, std::weak_ptr<Node> Origin,
           std::weak_ptr<Node> Destination, TransmissionBitrate Bitrate)  :
    CallRequisition(tOcurr, Event::CallRequisition, this),
    CallEnding(tOcurr + tDur, Event::CallEnding, this),
    Origin(Origin),
    Destination(Destination),
    Bitrate(Bitrate) {

}
