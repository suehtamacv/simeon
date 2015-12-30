#ifndef NSGA2_H
#define NSGA2_H

class NSGA2 {
  public:
    NSGA2();

    static constexpr double mutationProb = 0.1;
    static constexpr double breedingProb = 1;
    static constexpr unsigned int numGen = 300;
    static constexpr unsigned int numIndiv = 100;
};

#endif // NSGA2_H

