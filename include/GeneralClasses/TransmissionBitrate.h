#ifndef TRANSMISSIONBITRATE_H
#define TRANSMISSIONBITRATE_H

/**
 * @brief The TransmissionBitrate class represents a transmission bitrate.
 */
class TransmissionBitrate {
  public:
	TransmissionBitrate(long double Bitrate);
	long double get_Bitrate();
  private:
	long double Bitrate;
};

#endif // TRANSMISSIONBITRATE_H

