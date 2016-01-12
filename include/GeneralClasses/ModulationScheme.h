#ifndef MODULATIONSCHEME_H
#define MODULATIONSCHEME_H

#include <GeneralClasses/Gain.h>
#include <GeneralClasses/TransmissionBitrate.h>
#include <vector>

/**
 * @brief The ModulationScheme class represents a modulation scheme.
 */
class ModulationScheme
{
public:
#define DEFAULT_MODULATIONSCHEMES \
  X(4, Gain(6.8, Gain::dB)) \
  X(16, Gain(10.5, Gain::dB)) \
  X(64, Gain(14.8, Gain::dB)) //X Macros

    /**
     * @brief ModulationScheme is the standard constructor for a ModulationScheme.
     * @param M is the number of points in the QAM constellation.
     * @param SNR_Per_Bit is the minimum acceptable SNR per Bit in order to
     * implement a call with this modulation scheme.
     */
    ModulationScheme(unsigned int M, Gain SNR_Per_Bit);
    /**
     * @brief ModulationScheme is the copy constructor for a ModulationScheme.get_M()
     */
    ModulationScheme(const ModulationScheme &);
    /**
     * @brief get_M returns the number of points in the QAM constellation.
     * @return the number of points in the QAM constellation.
     */
    unsigned int get_M() const;
    /**
     * @brief get_SNR_Per_Bit returns the minimum acceptable SNR per Bit in order
     * to implement a call with this modulation scheme.
     * @return the minimum acceptable SNR per Bit in order to implement a call
     * with this modulation scheme.
     */
    Gain get_SNR_Per_Bit() const;

    /**
     * @brief operator = is the copy assignment of ModulationScheme.
     * @return a pointer to this.
     */
    ModulationScheme &operator=(const ModulationScheme &scheme);

    bool operator<(const ModulationScheme &scheme) const;
    bool operator>(const ModulationScheme &scheme) const;
    bool operator==(const ModulationScheme &scheme) const;

    /**
     * @brief get_ThresholdOSNR calculates the minimum OSNR acceptable to
     * implement a Call with this scheme and a certain TransmissionBitrate.
     * @param BitRate is the TransmissionBitrate of the Call.
     * @return the minimum OSNR acceptable to implement a Call with this scheme
     * and a certain TransmissionBitrate.
     */
    Gain get_ThresholdOSNR(TransmissionBitrate &BitRate);
    /**
     * @brief get_NumSlots calculates the number of slots necessary to implement
     * a Call with this scheme and a certain TransmissionBitrate.
     * @param BitRate is the TransmissionBitrate of the Call.
     * @return the number of slots necessary to implement a Call with this
     * scheme and a certain TransmissionBitrate.
     */
    unsigned int get_NumSlots(TransmissionBitrate &BitRate);
    /**
     * @brief DefaultSchemes is a vector with the default Modulation Schemes.
     */
    static std::vector<ModulationScheme> DefaultSchemes;

private:
    unsigned int M;
    Gain SNR_Per_Bit;
};

#endif // MODULATIONSCHEME_H
