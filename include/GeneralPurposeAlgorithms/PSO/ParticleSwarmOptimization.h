#ifndef PARTICLESWARMOPTIMIZATION_H
#define PARTICLESWARMOPTIMIZATION_H

#include <GeneralPurposeAlgorithms/PSO/PSO_Particle.h>
#include <vector>
#include <algorithm>
#include <iostream>

//! Particle Swarm Optimization
namespace PSO
{
/**
 * @brief The ParticleSwarmOptimization class is represents the PSO Algorithm.
 * Its simulates a swarm of particles, that travel over the solution spaces to find
 * a fit solution.
 * @tparam PositionType is the type of the "position" of a particle. For example,
 * a continuous travel would use a double or a long double.
 * @tparam Fitness is the class that is used to evaluate the fitness of each
 * particle. Such class must have a operator() that returns a PositionType, the
 * fitness of this particle.
 * @tparam Comparator is used to compare whether one particle is fitter than the
 * other. It must have a operator(PSO_Particle A, PSO_Particle B) that returs true
 * iff A is fitter than B.
 */
template<class PositionType, class Fitness, class Comparator>
class ParticleSwarmOptimization
{
public:
    /**
     * @brief ParticleSwarmOptimization is the standard constructor of a PSO Optimization.
     * @param P is the number of particles on each generation of the swarm.
     * @param G is the number of generations.
     * @param N is the number of dimensions of each particle's position.
     * @param XMin is the minimum possible position, on each dimension.
     * @param XMax is the maximum possible position, on each dimension.
     * @param VMin is the minimum possible velocity, on each dimension.
     * @param VMax is the maximum possible velocity, on each dimension.
     */
    ParticleSwarmOptimization(unsigned int P, unsigned int G, unsigned int N,
                              PositionType XMin, PositionType XMax, PositionType VMin, PositionType VMax);

    /**
     * @brief Particles is a vector with the current generation particles.
     */
    std::vector<std::shared_ptr<PSO_Particle<PositionType>>> Particles;
    /**
     * @brief BestParticle is a pointer to the best particle ever found.
     */
    std::shared_ptr<PSO_Particle<PositionType>> BestParticle;

    /**
     * @brief run_generation runs the next generation on the PSO Optimization.
     */
    void run_generation();

private:
    unsigned int P;
    unsigned int G;
    unsigned int N;

    int g;

    void updatePositions();

    PositionType XMin;
    PositionType XMax;
    PositionType VMin;
    PositionType VMax;

    static constexpr double c1 = 2.05;
    static constexpr double c2 = 2.05;
    static constexpr double phi = c1 + c2;
    double chi;

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
    chi = 2.0 / std::abs(2 - phi - sqrt(phi * phi - 4 * phi));

    //Create Particles
    Particles.resize(P);

    for (auto &particle : Particles)
        {
        particle = std::make_shared<PSO_Particle<PositionType>>(N, XMin, XMax);
        }

    //Create ring topology
    for (size_t particle = 0; particle < Particles.size(); ++particle)
        {
        if (particle != 0)
            {
            Particles[particle]->Neighbour[0] = Particles[particle - 1];
            }
        else
            {
            Particles[particle]->Neighbour[0] = Particles.back();
            }

        if (particle != Particles.size() - 1)
            {
            Particles[particle]->Neighbour[1] = Particles[particle + 1];
            }
        else
            {
            Particles[particle]->Neighbour[1] = Particles.front();
            }
        }

    BestParticle = Particles[0];
    g = 1;
}

template<class PositionType, class Fit, class Comp>
void ParticleSwarmOptimization<PositionType, Fit, Comp>::run_generation()
{
    #pragma omp parallel for ordered schedule(dynamic)

    for (size_t i = 0; i < Particles.size(); i++)
        {
        Particles[i]->currentFit = Fit()(Particles[i]);

        if (Comp()(Particles[i]->currentFit, Particles[i]->bestFit) || g == 1)
            {
            Particles[i]->bestFit = Particles[i]->currentFit;
            Particles[i]->P = Particles[i]->X;
            }

        #pragma omp critical
            {
            if (Comp()(Particles[i]->bestFit, BestParticle->bestFit))
                {
                std::clog << "New fitter particle found. Fit: " << Particles[i]->currentFit
                          << std::endl;

                BestParticle = Particles[i];
                }
            }
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
        for (size_t i = 0; i < N; i++)
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
        for (size_t i = 0; i < N; i++)
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
}

#endif // PARTICLESWARMOPTIMIZATION_H
