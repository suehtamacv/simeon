#include <GeneralClasses/TransmissionBitrate.h>

std::vector<TransmissionBitrate> TransmissionBitrate::DefaultBitrates =
{
#define X(a) TransmissionBitrate(a),
    DEFAULT_TRANSMISSIONBITRATES
#undef X
#undef DEFAULT_TRANSMISSIONBITRATES
};

TransmissionBitrate::TransmissionBitrate(double Bitrate)
{
    this->Bitrate = Bitrate;
}

TransmissionBitrate::TransmissionBitrate(const TransmissionBitrate &other)
{
    Bitrate = other.Bitrate;
}

double TransmissionBitrate::get_Bitrate() const
{
    return Bitrate;
}

bool TransmissionBitrate::operator <(const TransmissionBitrate &other) const
{
    return Bitrate < other.get_Bitrate();
}

bool TransmissionBitrate::operator ==(const TransmissionBitrate &other) const
{
    return Bitrate == other.get_Bitrate();
}

std::ostream& operator <<(std::ostream &out, const TransmissionBitrate &br)
{
    out << "BitRate: " << (br.Bitrate / 1E9) << "Gbps";
    return out;
}
