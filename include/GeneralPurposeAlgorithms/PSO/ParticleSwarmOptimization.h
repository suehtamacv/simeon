#ifndef PARTICLESWARMOPTIMIZATION_H
#define PARTICLESWARMOPTIMIZATION_H

#include <GeneralPurposeAlgorithms/PSO/PSO_Particle.h>

namespace PSO {

    template<class T>
    class ParticleSwarmOptimization {
      public:
        ParticleSwarmOptimization(unsigned int P, unsigned int G);

      private:
        unsigned int P;
        unsigned int G;
    };

}

#endif // PARTICLESWARMOPTIMIZATION_H
