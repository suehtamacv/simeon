#ifndef GAIN_H
#define GAIN_H

/**
 * @brief The Gain class provides a interface to gain variables that are measured in dB units or in linear units.
 */
class Gain
{
public:
    /**
     * @brief The InitType enum is used to choose how to init the object.
     */
    enum InitType
    {
        dB, /*!< Use dB to provide an initial value in dB */
        Linear /*!< Use Linear to provide an initial value in linear units */
    };

    /**
     * @brief dB is the standard constructor.
     * @param value is the value of this object, either in linear or in dB units.
     * @param Type is used to choose between value measured in linear or in dB units.
     */
    Gain(double value, InitType Type = dB);
    /**
     * @brief Gain is the copy constructor of Gain.
     */
    Gain(const Gain &);

    /**
     * @brief operator - returns the symmetrical Gain.
     * @return the symmetrical Gain.
     */
    Gain operator -();
    /**
     * @brief operator + returns the net gain after summing two successive gains.
     * @return the net gain after summing two successive gains.
     */
    Gain operator+(Gain &);
    /**
     * @brief operator - returns the net gain after subtracting two successive gains.
     * @return the net gain after subtracting two successive gains.
     */
    Gain operator-(Gain &);

    bool operator>(const Gain &) const;
    bool operator<(const Gain &) const;
    bool operator==(const Gain &) const;
    bool operator>=(const Gain &) const;
    bool operator<=(const Gain &) const;

    /**
     * @brief in_dB returns the value of this object in dB units.
     * @return the value of this object in dB units.
     */
    double in_dB() const;
    /**
     * @brief in_Linear returns the value of this object in linear units.
     * @return the value of this object in linear units.
     */
    double in_Linear();

private:
    double value_dB;
    double value_Linear;
    bool calculatedLinear;
};

#endif // GAIN_H
