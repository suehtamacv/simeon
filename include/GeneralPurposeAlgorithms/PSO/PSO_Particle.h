#ifndef PSO_PARTICLE_H
#define PSO_PARTICLE_H

#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <GeneralClasses/RandomGenerator.h>

template<class PositionType>
class PSO_Particle
{
public:
    PSO_Particle(unsigned int N, PositionType XMin, PositionType XMax);
    void initialize(PositionType XMin, PositionType XMax);

    std::vector<PositionType> X; //Position
    std::vector<PositionType> V; //Velocity
    std::vector<PositionType> P; //Best position so far

    PositionType currentFit;
    PositionType bestFit;

    std::weak_ptr<PSO_Particle> Neighbour[2];

private:
    unsigned int N;
};

template<class PositionType>
PSO_Particle<PositionType>::PSO_Particle(
    unsigned int N, PositionType XMin, PositionType XMax) : N(N)
{
    X.resize(N);
    V.resize(N);
    P.resize(N);
    initialize(XMin, XMax);
}

template<class PositionType>
void PSO_Particle<PositionType>::initialize(
    PositionType XMin, PositionType XMax)
{

    std::uniform_real_distribution<PositionType> distribution(XMin, XMax);
    for (auto &x : X)
        {
        x = distribution(random_generator);
        }
}

#endif // PSO_PARTICLE_H
