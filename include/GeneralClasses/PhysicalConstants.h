#ifndef PHYSICALCONSTANTS_H
#define PHYSICALCONSTANTS_H

class PhysicalConstants {
	public:
		/**
		 * @brief c is the light's velocity.
		 */
		constexpr static long double c = 299792458;
		/**
		 * @brief h is the Planck's constant.
		 */
		constexpr static long double h = 6.62606957E-34;
		/**
		 * @brief lambda is the light's wavelength.
		 */
		constexpr static long double lambda = 1550E-9;
		/**
		 * @brief freq is the light's frequency;
		 */
		constexpr static long double freq = c / lambda;
};

#endif // PHYSICALCONSTANTS_H

