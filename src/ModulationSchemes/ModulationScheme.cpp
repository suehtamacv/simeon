#include <ModulationSchemes/ModulationScheme.h>

ModulationScheme::ModulationScheme(unsigned int M,
        Gain SNR_Per_Bit) : SNR_Per_Bit(SNR_Per_Bit) {
    this->M = M;
}

unsigned int ModulationScheme::get_M() {
    return M;
}

Gain ModulationScheme::get_SNR_Per_Bit() {
    return SNR_Per_Bit;
}
