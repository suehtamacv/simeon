#include <cmath>
#include <GeneralClasses/ModulationScheme.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <Structure/Slot.h>

std::set<ModulationScheme> ModulationScheme::DefaultSchemes =
{
#define X(a,b)  ModulationScheme(a,b),
    DEFAULT_MODULATIONSCHEMES
#undef X
#undef DEFAULT_MODULATIONSCHEMES
};

ModulationScheme::ModulationScheme(unsigned int M, Gain SNR_Per_Bit)
    : M(M), SNR_Per_Bit(SNR_Per_Bit)
{
}

ModulationScheme::ModulationScheme(const ModulationScheme &scheme) :
    SNR_Per_Bit(scheme.SNR_Per_Bit)
{
    M = scheme.M;
}

ModulationScheme &ModulationScheme::operator =(const ModulationScheme &scheme)
{
    M = scheme.M;
    SNR_Per_Bit = scheme.SNR_Per_Bit;
    return *this;
}

unsigned int ModulationScheme::get_M() const
{
    return M;
}

Gain ModulationScheme::get_SNR_Per_Bit() const
{
    return SNR_Per_Bit;
}

bool ModulationScheme::operator <(const ModulationScheme &scheme) const
{
    return (M < scheme.M);
}

bool ModulationScheme::operator >(const ModulationScheme &scheme) const
{
    return (M > scheme.M);
}

bool ModulationScheme::operator ==(const ModulationScheme &scheme) const
{
    return (M == scheme.M);
}

Gain ModulationScheme::get_ThresholdOSNR(TransmissionBitrate &BitRate) const
{
    return Gain(0.5 * BitRate.get_Bitrate() * pow10(0.1 * SNR_Per_Bit.in_dB()) /
                PhysicalConstants::BRef, Gain::Linear);
}

unsigned int ModulationScheme::get_NumSlots(TransmissionBitrate &BitRate) const
{
    return ceil(BitRate.get_Bitrate() / (Slot::BSlot *
                                         PhysicalConstants::numPolarizations *
                                         log2(M)));
}

std::ostream& operator <<(std::ostream &out, const ModulationScheme &scheme)
{
    out << "Scheme: " << scheme.M << "QAM";
    return out;
}
