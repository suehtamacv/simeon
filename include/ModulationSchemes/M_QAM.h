#ifndef MODULATIONSCHEME_H
#define MODULATIONSCHEME_H

#include <GeneralClasses/Gain.h>
#include <GeneralClasses/TransmissionBitrate.h>

/**
 * @brief The ModulationScheme class represents a modulation scheme.
 */
class M_QAM {
  public:
    M_QAM(unsigned int M, Gain SNR_Per_Bit);
    unsigned int get_M();
    Gain get_SNR_Per_Bit();

    bool operator<(M_QAM Scheme) const;
    bool operator>(M_QAM Scheme) const;

    Gain get_ThresholdOSNR(TransmissionBitrate BitRate);
    unsigned int get_NumSlots(TransmissionBitrate BitRate);
  private:
    unsigned int M;
    Gain SNR_Per_Bit;
};

#endif // MODULATIONSCHEME_H
