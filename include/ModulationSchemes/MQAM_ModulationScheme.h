#ifndef MQAM_MODULATIONSCHEME_H
#define MQAM_MODULATIONSCHEME_H

#include <GeneralClasses/dB.h>
#include <ModulationSchemes/ModulationScheme.h>

class MQAM_ModulationScheme : public ModulationScheme {
  public:
    MQAM_ModulationScheme(unsigned int M, dB SNR_Per_Bit);
    unsigned int get_M();
    dB get_SNR_Per_Bit();

  private:
    unsigned int M;
    dB SNR_Per_Bit;
};

#endif // MQAM_MODULATIONSCHEME_H
