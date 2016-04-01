#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H

#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <GeneralClasses/RandomGenerator.h>

/**
 * @brief The PSO_Particle class represents a particle to the PSO Optimization.
 * @tparam PositionType represents the same that the homonym class represents on
 * the ParticleSwarmOptimization.
 */
template<class PositionType>
class PSO_Particle
{
public:
    /**
     * @brief PSO_Particle is the standard constructor for a particle on the PSO
     * optimization.
     * @param N is the number of dimensions on this particle's position.
     * @param XMin is the minimum possible position, on each dimension.
     * @param XMax is the maximum possible position, on each dimension.
     */
    PSO_Particle(unsigned int N, PositionType XMin, PositionType XMax);

    std::vector<PositionType> X; //Position
    std::vector<PositionType> V; //Velocity
    std::vector<PositionType> P; //Best position so far

    /**
     * @brief currentFit is the current fit of this particle.
     */
    PositionType currentFit;
    /**
     * @brief bestFit is the best fit ever found by this particle.
     */
    PositionType bestFit;
    /**
     * @brief Neighbour are pointers to this particle neighbours.
     */
    std::weak_ptr<PSO_Particle> Neighbour[2];

private:
    unsigned int N;
    void initialize(PositionType XMin, PositionType XMax);

};

template<class PositionType>
PSO_Particle<PositionType>::PSO_Particle(
    unsigned int N, PositionType XMin, PositionType XMax) : N(N)
{
    X.resize(N, 0);
    V.resize(N, 0);
    P.resize(N, 0);
    initialize(XMin, XMax);
}

template<class PositionType>
void PSO_Particle<PositionType>::initialize(PositionType, PositionType XMax)
{

    std::uniform_real_distribution<PositionType> distribution(0, XMax);
    for (auto &x : X)
        {
        x = distribution(random_generator);
        }
}

#endif // PSO_PARTICLE_H
