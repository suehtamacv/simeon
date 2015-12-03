#ifndef MQAM_MODULATIONSCHEME_H
#define MQAM_MODULATIONSCHEME_H

#include <GeneralClasses/Gain.h>
#include <ModulationSchemes/ModulationScheme.h>

class MQAM_ModulationScheme : public ModulationScheme {
  public:
    MQAM_ModulationScheme(unsigned int M, Gain SNR_Per_Bit);
    unsigned int get_M();
    Gain get_SNR_Per_Bit();

  private:
    unsigned int M;
    Gain SNR_Per_Bit;
};

#endif // MQAM_MODULATIONSCHEME_H
