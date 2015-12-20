#include <GeneralPurposeAlgorithms/PSO/ParticleSwarmOptimization.h>
#include <algorithm>

template<class T, class Fit, class Comp>
PSO::ParticleSwarmOptimization<T, Fit, Comp>::ParticleSwarmOptimization(
    unsigned int P,
    unsigned int G,
    unsigned int N,
    T XMin,
    T XMax,
    T VMin,
    T VMax) :
    P(P), G(G), N(N), XMin(XMin), XMax(XMax), VMin(VMin), VMax(VMax) {

    //Create Particles
    Particles.reserve(P);
    std::fill_n(Particles.begin(), P,
                std::shared_ptr<PSO_Particle<T, Fit, Comp>>(
                    new PSO_Particle<T, Fit, Comp>(N, XMin, XMax)));

    //Create ring topology
    for (int particle = 0; particle < Particles.size(); ++particle) {
        Particles[particle]->Neighbour[0] = Particles[(particle + 1) % P];
        Particles[particle]->Neighbour[1] = Particles[(particle - 1) % P];
    }

    BestParticle = Particles[0];
}

template<class T, class Fit, class Comp>
void PSO::ParticleSwarmOptimization<T, Fit, Comp>::run_generation() {
    for (auto particle : Particles) {
        particle->eval_Fitness();

        if (Comp(particle, BestParticle)) {
            BestParticle = particle;
        }
    }

    updatePositions();
}

template<class T, class Fit, class Comp>
void PSO::ParticleSwarmOptimization<T, Fit, Comp>::updatePositions() {

    std::uniform_real_distribution<long double> distribution(0, 1);
    std::default_random_engine generator;

    for (auto particle : Particles) {

        auto FitterNeigh = Comp(particle->Neighbour[0], particle->Neighbour[1]) ?
                           particle->Neighbour[0].lock() : particle->Neighbour[1].lock();

        //Calculate velocities
        for (int i = 0; i < N; i++) {
            long double Eps1 = distribution(generator);
            long double Eps2 = distribution(generator);

            particle->V[i] += c1 * Eps1 * (particle->P[i] - particle->X[i]);
            particle->V[i] += c2 * Eps2 * (FitterNeigh->P[i] - particle->X[i]);
            particle->V[i] *= chi;

            if (particle->V[i] > VMax) {
                particle->V[i] = VMax;
            } else if (particle->V[i] < VMin) {
                particle->V[i] = VMin;
            }
        }

        //Calculate positions
        for (int i = 0; i < N; i++) {
            particle->X[i] += particle->V[i];

            if (particle->X[i] > XMax) {
                particle->X[i] = XMax;
            } else if (particle->X[i] < XMin) {
                particle->X[i] = XMin;
            }

        }
    }
}
