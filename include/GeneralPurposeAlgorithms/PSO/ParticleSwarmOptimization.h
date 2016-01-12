#ifndef PARTICLESWARMOPTIMIZATION_H
#define PARTICLESWARMOPTIMIZATION_H

#include <GeneralPurposeAlgorithms/PSO/PSO_Particle.h>
#include <vector>
#include <algorithm>
#include <iostream>

template<class PositionType, class Fitness, class Comparator>
class ParticleSwarmOptimization
{
public:
    ParticleSwarmOptimization(unsigned int P, unsigned int G, unsigned int N,
                              PositionType XMin, PositionType XMax, PositionType VMin, PositionType VMax);

    std::vector<std::shared_ptr<PSO_Particle<PositionType>>> Particles;

    std::shared_ptr<PSO_Particle<PositionType>> BestParticle;

    void run_generation();

private:
    unsigned int P;
    unsigned int G;
    unsigned int N;

    int g;
    int p;

    void updatePositions();

    PositionType XMin;
    PositionType XMax;
    PositionType VMin;
    PositionType VMax;

    static constexpr double c1 = 2.05;
    static constexpr double c2 = 2.05;
    static constexpr double phi = c1 + c2;
    static constexpr double chi = 2.0 / std::abs(2 - phi - sqrt(
                                      phi * phi - 4 * phi));

};

template<class PositionType, class Fit, class Comp>
ParticleSwarmOptimization<PositionType, Fit, Comp>::ParticleSwarmOptimization(
    unsigned int P,
    unsigned int G,
    unsigned int N,
    PositionType XMin,
    PositionType XMax,
    PositionType VMin,
    PositionType VMax) :
    P(P), G(G), N(N), XMin(XMin), XMax(XMax), VMin(VMin), VMax(VMax)
{

    //Create Particles
    Particles.resize(P);

    for (auto &particle : Particles)
        {
            particle = std::shared_ptr<PSO_Particle<PositionType>>(
                           new PSO_Particle<PositionType>(N, XMin, XMax));
        }

    //Create ring topology
    for (unsigned particle = 0; particle < Particles.size(); ++particle)
        {
            Particles[particle]->Neighbour[0] = Particles[(particle + 1) % P];
            Particles[particle]->Neighbour[1] = Particles[(particle - 1) % P];
        }

    BestParticle = Particles[0];
    p = g = 1;
}

template<class PositionType, class Fit, class Comp>
void ParticleSwarmOptimization<PositionType, Fit, Comp>::run_generation()
{
    p = 1;

    #pragma omp parallel for ordered schedule(dynamic)

    for (unsigned i = 0; i < Particles.size(); i++)
        {
            Particles[i]->currentFit = Fit()(Particles[i]);

            if (Comp()(Particles[i]->currentFit, Particles[i]->bestFit) || g == 1)
                {
                    Particles[i]->bestFit = Particles[i]->currentFit;
                    Particles[i]->P = Particles[i]->X;
                }

            #pragma omp critical
            if (Comp()(Particles[i]->bestFit, BestParticle->bestFit))
                {
                    std::clog << "New fitter particle found. Fit: " << Particles[i]->currentFit
                              << std::endl;

                    BestParticle = Particles[i];
                }

            p++;
        }

    updatePositions();
    g++;
}

template<class PositionType, class Fit, class Comp>
void ParticleSwarmOptimization<PositionType, Fit, Comp>::updatePositions()
{

    std::uniform_real_distribution<double> PSO_UnifDistribution(0, 1);

    for (auto &particle : Particles)
        {

            auto FitterNeigh = Comp()(particle->Neighbour[0].lock()->currentFit,
                                      particle->Neighbour[1].lock()->currentFit) ?
                               particle->Neighbour[0].lock() : particle->Neighbour[1].lock();

            //Calculate velocities
            for (unsigned i = 0; i < N; i++)
                {
                    double Eps1 = PSO_UnifDistribution(random_generator);
                    double Eps2 = PSO_UnifDistribution(random_generator);

                    particle->V[i] += c1 * Eps1 * (particle->P[i] - particle->X[i]);
                    particle->V[i] += c2 * Eps2 * (FitterNeigh->P[i] - particle->X[i]);
                    particle->V[i] *= chi;

                    if (particle->V[i] > VMax)
                        {
                            particle->V[i] = VMax;
                        }
                    else if (particle->V[i] < VMin)
                        {
                            particle->V[i] = VMin;
                        }
                }

            //Calculate positions
            for (unsigned i = 0; i < N; i++)
                {
                    particle->X[i] += particle->V[i];

                    if (particle->X[i] > XMax)
                        {
                            particle->X[i] = XMax;
                        }
                    else if (particle->X[i] < XMin)
                        {
                            particle->X[i] = XMin;
                        }
                }
        }
}

#endif // PARTICLESWARMOPTIMIZATION_H
