#ifndef POWER_H
#define POWER_H

#include <GeneralClasses/Gain.h>

class Power {
  public:
	/**
	* @brief The InitType enum is used to choose how to init the object. Use dBm to provide an initial value in dBm, and Watt to provide an initial value in watts.
	*/
	enum InitType {
		dBm, Watt
	};
	Power(long double value, InitType = dBm);
	Power(const Power&);

	Power operator*(Gain G);
	Power operator+(Power P);
	void operator*=(Gain G);
	void operator+=(Power P);

	long double in_dBm() const;
	long double in_Watts() const;
  private:
	long double value_dBm;
	long double value_Watts;
};

#endif // POWER_H
