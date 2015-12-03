#ifndef GAIN_H
#define GAIN_H

/**
 * @brief The Gain class provides a interface to gain variables that are measured in dB units or in linear units.
 */
class Gain {
  public:
	/**
	 * @brief The InitType enum is used to choose how to init the object. Use dB to provide an initial value in dB, and Linear to provide an initial value in linear units.
	 */
	enum InitType {
		dB, Linear
	};

	/**
	 * @brief dB is the standard constructor.
	 * @param value is the value of this object, either in linear or in dB units.
	 * @param Type is used to choose between value measured in linear or in dB units.
	 */
	Gain(long double value, InitType Type = dB);
	Gain(const Gain &);

	/**
	 * @brief operator - returns the symmetrical Gain.
	 * @return the symmetrical Gain.
	 */
	Gain operator-();
	/**
	 * @brief operator + returns the net gain after summing two successive gains.
	 * @return net gain after summing two successive gains.
	 */
	Gain operator+(Gain);
	Gain operator-(Gain);

	/**
	 * @brief in_dB returns the value of this object in dB units.
	 * @return the value of this object in dB units.
	 */
	long double in_dB() const;
	/**
	 * @brief in_Linear returns the value of this object in linear units.
	 * @return the value of this object in linear units.
	 */
	long double in_Linear() const;

  private:
	long double value_dB;
	long double value_Linear;
};

#endif // GAIN_H
