#include <cmath>
#include <GeneralClasses/ModulationScheme.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <Structure/Slot.h>

ModulationScheme::ModulationScheme(unsigned int M, Gain SNR_Per_Bit)
    : M(M), SNR_Per_Bit(SNR_Per_Bit) {
}

ModulationScheme::ModulationScheme(const ModulationScheme &scheme) :
    SNR_Per_Bit(scheme.SNR_Per_Bit) {
    M = scheme.M;
}

ModulationScheme &ModulationScheme::operator =(const ModulationScheme &scheme) {
    M = scheme.M;
    SNR_Per_Bit = scheme.SNR_Per_Bit;
    return *this;
}

unsigned int ModulationScheme::get_M() const {
    return M;
}

Gain ModulationScheme::get_SNR_Per_Bit() const {
    return SNR_Per_Bit;
}

bool ModulationScheme::operator <(const ModulationScheme &scheme) const {
    return (M < scheme.get_M());
}

bool ModulationScheme::operator >(const ModulationScheme &scheme) const {
    return (M > scheme.get_M());
}

bool ModulationScheme::operator ==(const ModulationScheme &scheme) const {
    return ((M == scheme.get_M()) && (SNR_Per_Bit == scheme.get_SNR_Per_Bit()));
}

Gain ModulationScheme::get_ThresholdOSNR(TransmissionBitrate &BitRate) {
    return Gain(0.5 * BitRate.get_Bitrate() * SNR_Per_Bit.in_Linear() /
                PhysicalConstants::BRef, Gain::Linear);
}

unsigned int ModulationScheme::get_NumSlots(TransmissionBitrate &BitRate) {
    return ceil(BitRate.get_Bitrate() / (Slot::BSlot *
                                         PhysicalConstants::numPolarizations *
                                         log2(M)));
}
