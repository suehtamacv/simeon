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
};

#endif // EDFA_H
