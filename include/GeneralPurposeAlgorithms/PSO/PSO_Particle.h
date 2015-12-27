#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H

#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <GeneralClasses/RandomGenerator.h>

namespace PSO {
    template<class T>
    class PSO_Particle {

      public:

        PSO_Particle(unsigned int N, T XMin, T XMax);
        void initialize(T XMin, T XMax);

        std::vector<T> X; //Position
        std::vector<T> V; //Velocity
        std::vector<T> P; //Best position so far

        T currentFit;
        T bestFit;

        std::weak_ptr<PSO_Particle> Neighbour[2];

      private:
        unsigned int N;
    };

    template<class T>
    PSO::PSO_Particle<T>::PSO_Particle(unsigned int N, T XMin, T XMax) : N(N) {
        X.resize(N);
        V.resize(N);
        P.resize(N);
        initialize(XMin, XMax);
    }

    template<class T>
    void PSO::PSO_Particle<T>::initialize(T XMin, T XMax) {
        std::uniform_real_distribution<T> distribution(XMin, XMax);

        for (auto &x : X) {
            x = distribution(random_generator);
        }
    }
}

#endif // PSO_PARTICLE_H
