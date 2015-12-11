#ifndef MODULATIONSCHEME_H
#define MODULATIONSCHEME_H

#include <GeneralClasses/Gain.h>
#include <GeneralClasses/TransmissionBitrate.h>

/**
 * @brief The ModulationScheme class represents a modulation scheme.
 */
class ModulationScheme {
  public:
    ModulationScheme(unsigned int M, Gain SNR_Per_Bit);
    unsigned int get_M() const;
    Gain get_SNR_Per_Bit() const;

    ModulationScheme &operator=(const ModulationScheme &scheme);

    bool operator<(const ModulationScheme &scheme) const;
    bool operator>(const ModulationScheme &scheme) const;
    bool operator==(const ModulationScheme &scheme) const;

    Gain get_ThresholdOSNR(TransmissionBitrate BitRate);
    unsigned int get_NumSlots(TransmissionBitrate BitRate);

  private:
    unsigned int M;
    Gain SNR_Per_Bit;
};

#endif // MODULATIONSCHEME_H
