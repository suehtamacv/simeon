#include <GeneralClasses/TransmissionBitrate.h>

std::vector<TransmissionBitrate> TransmissionBitrate::DefaultBitrates = {
#define X(a) TransmissionBitrate(a),
    DEFAULT_TRANSMISSIONBITRATES
#undef X
#undef DEFAULT_TRANSMISSIONBITRATES
};

TransmissionBitrate::TransmissionBitrate(double Bitrate) {
    this->Bitrate = Bitrate;
}

double TransmissionBitrate::get_Bitrate() {
    return Bitrate;
}
