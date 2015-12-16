#include <GeneralClasses/TransmissionBitrate.h>

std::vector<TransmissionBitrate> TransmissionBitrate::DefaultBitrates = {
#define X(a) TransmissionBitrate(a),
    DEFAULT_TRANSMISSIONBITRATES
#undef X
#undef DEFAULT_TRANSMISSIONBITRATES
};

TransmissionBitrate::TransmissionBitrate(long double Bitrate) {
    this->Bitrate = Bitrate;
}

long double TransmissionBitrate::get_Bitrate() {
    return Bitrate;
}
