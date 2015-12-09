#include <cmath>
#include <ModulationSchemes/ModulationScheme.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <Structure/Slot.h>

ModulationScheme::ModulationScheme(unsigned int M, Gain SNR_Per_Bit)
    : M(M), SNR_Per_Bit(SNR_Per_Bit) {
}

unsigned int ModulationScheme::get_M() {
    return M;
}

Gain ModulationScheme::get_SNR_Per_Bit() {
    return SNR_Per_Bit;
}

bool ModulationScheme::operator <(ModulationScheme Scheme) const {
    if (M < Scheme.get_M()) {
        return true;
    }

    return false;
}

bool ModulationScheme::operator >(ModulationScheme Scheme) const {
    if (M > Scheme.get_M()) {
        return true;
    }

    return false;
}

Gain ModulationScheme::get_ThresholdOSNR(TransmissionBitrate BitRate) {
    return Gain(0.5 * BitRate.get_Bitrate() * SNR_Per_Bit.in_Linear() /
                PhysicalConstants::BRef, Gain::Linear);
}

unsigned int ModulationScheme::get_NumSlots(TransmissionBitrate BitRate) {
    return ceil(BitRate.get_Bitrate() / (Slot::BSlot *
                                         PhysicalConstants::numPolarizations *
                                         log2(M)));
}
