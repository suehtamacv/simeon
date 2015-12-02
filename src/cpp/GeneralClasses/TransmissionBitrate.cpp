#include <GeneralClasses/TransmissionBitrate.h>

TransmissionBitrate::TransmissionBitrate(long double Bitrate) {
    this->Bitrate = Bitrate;
}

long double TransmissionBitrate::get_Bitrate() {
    return Bitrate;
}
