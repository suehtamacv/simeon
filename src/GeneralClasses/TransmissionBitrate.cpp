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

bool TransmissionBitrate::operator ==(const TransmissionBitrate &br) const
{
    return Bitrate == br.get_Bitrate();
}

bool TransmissionBitrate::operator !=(const TransmissionBitrate &br) const
{
    return !(operator ==(br));
}

bool TransmissionBitrate::operator <(const TransmissionBitrate &br) const
{
    return (Bitrate < br.get_Bitrate());
}

bool TransmissionBitrate::operator <=(const TransmissionBitrate &br) const
{
    return ((operator ==(br)) || (operator <(br)));
}

bool TransmissionBitrate::operator >(const TransmissionBitrate &br) const
{
    return (Bitrate > br.get_Bitrate());
}

bool TransmissionBitrate::operator >=(const TransmissionBitrate &br) const
{
    return ((operator ==(br)) || (operator >(br)));
}

std::ostream& operator <<(std::ostream &out, const TransmissionBitrate &br)
{
    return out << (br.Bitrate / 1E9) << "Gbps";
}
