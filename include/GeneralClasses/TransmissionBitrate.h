#ifndef TRANSMISSIONBITRATE_H
#define TRANSMISSIONBITRATE_H

#include <vector>

/**
 * @brief The TransmissionBitrate class represents a transmission bitrate.
 */
class TransmissionBitrate
{
public:
#define DEFAULT_TRANSMISSIONBITRATES \
  X(10E9) \
  X(40E9) \
  X(100E9) \
  X(160E9) \
  X(400E9)

    /**
     * @brief TransmissionBitrate is the standard constructor for a TransmissionBitrate.
     * @param Bitrate is the bitrate, in bits per second.
     */
    TransmissionBitrate(double Bitrate);
    TransmissionBitrate(const TransmissionBitrate &);
    /**
     * @brief get_Bitrate returns the value of the bitrate, in bits per second.
     * @return the value of the bitrate, in bits per second.
     */
    double get_Bitrate() const;

    bool operator <(const TransmissionBitrate &) const;
    bool operator ==(const TransmissionBitrate &) const;

    static std::vector<TransmissionBitrate> DefaultBitrates;
private:
    double Bitrate;
};

#endif // TRANSMISSIONBITRATE_H

