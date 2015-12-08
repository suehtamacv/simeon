#ifndef EDFA_H
#define EDFA_H

#include <Devices/Amplifiers/Amplifier.h>

/**
 * @brief The EDFA class represents an Erbium Doped Fiber Amplifier. This class
 * of amplifiers has a ASE Noise Power modelling.
 */
class EDFA : public Amplifier {
  public:
    EDFA(Gain G);

  private:
    void calculate_NoisePower();

    /**
     * @brief NoiseFigure is the noise figure of the amplifiers.
     */
    static Gain NoiseFigure;
    /**
     * @brief numPolarizations is used to choose whether one or two polarizations are used to transmit the signal.
     */
    constexpr static int numPolarizations = 2;
};

#endif // EDFA_H
