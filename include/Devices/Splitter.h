#ifndef SPLITTER_H
#define SPLITTER_H

#include <Devices/Device.h>

/**
 * @brief The Splitter class represents a Splitter. Is only used with the
 * Broadcast-And-Select node architecture.
 */
class Splitter : public Device {
  public:
	static constexpr DeviceType DevType = Device::SplitterDevice;

    /**
     * @brief Splitter is the standard constructor for a splitter.
     * @param NumPorts is the number of ports of the splitter.
     */
	Splitter(int NumPorts);

	Gain get_Gain();
	Power get_Noise();

	void set_NumPorts(int NumPorts);

  private:
	int NumPorts;
	Gain SplitterLoss;
};

#endif // SPLITTER_H
