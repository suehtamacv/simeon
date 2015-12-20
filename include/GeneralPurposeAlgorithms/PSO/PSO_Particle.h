#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H

#include <memory>
#include <vector>
#include <cmath>

namespace PSO {

    template<class T, class Fit, class Comp>
    class PSO_Particle {

      public:

        PSO_Particle(unsigned int N, T XMin, T XMax);
        void initialize(T XMin, T XMax);

        std::vector<T> X; //Position
        std::vector<T> V; //Velocity
        std::vector<T> P; //Best position so far

        bool operator >(const PSO_Particle &);
        T eval_Fitness();
        T currentFit;
        T bestFit;

        std::weak_ptr<PSO_Particle> Neighbour[2];

      private:

        unsigned int N;

        static constexpr long double c1 = 2.05L;
        static constexpr long double c2 = 2.05L;
        static constexpr long double phi = c1 + c2;
        static constexpr long double chi = 2.0L / fabs(2 - phi - sqrt(
                                               phi * phi - 4 * phi));

    };

}

#endif // PSO_PARTICLE_H
