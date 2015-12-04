#ifndef EDFA_H
#define EDFA_H

#include <Devices/Amplifiers/Amplifier.h>

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
     * @brief BRef is the reference bandwidth. Is a parameter for the ASE Noise modelling.
     */
    static constexpr long double BRef = 12.5E9;
    /**
     * @brief numPolarizations is used to choose whether one or two polarizations are used to transmit the signal.
     */
    constexpr static int numPolarizations = 2;
};

#endif // EDFA_H
