#include <ModulationSchemes/MQAM_ModulationScheme.h>

MQAM_ModulationScheme::MQAM_ModulationScheme(unsigned int M,
        Gain SNR_Per_Bit) : SNR_Per_Bit(SNR_Per_Bit) {
    this->M = M;
}

unsigned int MQAM_ModulationScheme::get_M() {
    return M;
}

Gain MQAM_ModulationScheme::get_SNR_Per_Bit() {
    return SNR_Per_Bit;
}
