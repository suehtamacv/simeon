#include <GeneralPurposeAlgorithms/PSO/PSO_Particle.h>
#include <algorithm>
#include <random>

template<class T, class Fit, class Comp>
PSO::PSO_Particle<T, Fit, Comp>::PSO_Particle(
    unsigned int N, T XMin, T XMax) : N(N) {
    X.reserve(N);
    V.reserve(N);
    P.reserve(N);
    initialize(XMin, XMax);
}

template<class T, class Fit, class Comp>
bool PSO::PSO_Particle<T, Fit, Comp>::operator >(const PSO_Particle &other) {
    return Compare(currentFit, other.currentFit);
}

template<class T, class Fit, class Comp>
T PSO::PSO_Particle<T, Fit, Comp>::eval_Fitness() {
    currentFit = Fit(&this);

    if (Comp(currentFit, bestFit)) {
        bestFit = currentFit;
    }

    return currentFit;
}

template<class T, class Fit, class Comp>
void PSO::PSO_Particle<T, Fit, Comp>::initialize(T XMin, T XMax) {
    std::generate(X.begin(), X.end(),
                  std::uniform_real_distribution<T>(XMin, XMax)(std::default_random_engine()));
}
