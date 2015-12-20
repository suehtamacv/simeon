#ifndef PARTICLESWARMOPTIMIZATION_H
#define PARTICLESWARMOPTIMIZATION_H

#include <GeneralPurposeAlgorithms/PSO/PSO_Particle.h>
#include <vector>

namespace PSO {

    template<class T, class Fit, class Comp>
    class ParticleSwarmOptimization {
      public:
        ParticleSwarmOptimization(unsigned int P, unsigned int G, unsigned int N,
                                  T XMin, T XMax, T VMin, T VMax);

        std::vector<std::shared_ptr<PSO_Particle<T, Fit, Comp>>> Particles;

        std::shared_ptr<PSO_Particle<T, Fit, Comp>> BestParticle;

        void run_generation();

      private:
        unsigned int P;
        unsigned int G;
        unsigned int N;

        void updatePositions();

        T XMin;
        T XMax;
        T VMin;
        T VMax;

        static constexpr long double c1 = 2.05L;
        static constexpr long double c2 = 2.05L;
        static constexpr long double phi = c1 + c2;
        static constexpr long double chi = 2.0L / std::abs(2 - phi - sqrt(
                                               phi * phi - 4 * phi));

    };

}

#endif // PARTICLESWARMOPTIMIZATION_H
