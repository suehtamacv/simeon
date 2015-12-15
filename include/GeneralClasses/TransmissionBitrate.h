#ifndef TRANSMISSIONBITRATE_H
#define TRANSMISSIONBITRATE_H

/**
 * @brief The TransmissionBitrate class represents a transmission bitrate.
 */
class TransmissionBitrate {
  public:
    /**
     * @brief TransmissionBitrate is the standard constructor for a TransmissionBitrate.
     * @param Bitrate is the bitrate, in bits per second.
     */
	TransmissionBitrate(long double Bitrate);
    /**
     * @brief get_Bitrate returns the value of the bitrate, in bits per second.
     * @return the value of the bitrate, in bits per second.
     */
	long double get_Bitrate();
  private:
	long double Bitrate;
};

#endif // TRANSMISSIONBITRATE_H

