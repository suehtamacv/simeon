#ifndef POWER_H
#define POWER_H

#include <GeneralClasses/Gain.h>

class Power {
  public:
	/**
	* @brief The InitType enum is used to choose how to init the object. Use init_dBm to provide an initial value in dBm, and init_Watt to provide an initial value in watts.
	*/
	enum InitType {
		init_dBm, init_Watt
	};
	Power(long double value, InitType = init_dBm);

	Power operator*(Gain G);

	long double in_dBm() const;
	long double in_Watts() const;
  private:
	long double value_dBm;
	long double value_Watts;
};

#endif // POWER_H
