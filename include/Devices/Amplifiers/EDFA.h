#ifndef EDFA_H
#define EDFA_H

#include <Devices/Amplifiers/Amplifier.h>

/**
 * @brief The EDFA class represents an erbium doped fiber amplifier. This class
 * of amplifiers has a ASE noise power modelling.
 */
class EDFA : public Amplifier {
  public:
    /**
     * @brief EDFA is the standard constructor of a EDFA.
     * @param G is the Gain of this amplifier.
     */
    EDFA(Gain G);

  private:
    void calculate_NoisePower();

    /**
     * @brief NoiseFigure is the noise figure of the amplifiers.
     */
    static Gain NoiseFigure;
};

#endif // EDFA_H
