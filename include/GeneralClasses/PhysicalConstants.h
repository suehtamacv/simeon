#ifndef PHYSICALCONSTANTS_H
#define PHYSICALCONSTANTS_H

/**
 * @brief The PhysicalConstants class stores physical constants.
 */
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
        /**
         * @brief BRef is the reference bandwidth.
         */
        static constexpr long double BRef = 12.5E9;
};

#endif // PHYSICALCONSTANTS_H

