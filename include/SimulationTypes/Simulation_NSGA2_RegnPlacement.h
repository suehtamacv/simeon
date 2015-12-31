#ifndef SIMULATION_NSGA2_REGENERATORPLACEMENT_H
#define SIMULATION_NSGA2_REGENERATORPLACEMENT_H

#include "SimulationType.h"
#include <GeneralPurposeAlgorithms/NSGA-2.h>

class Simulation_NSGA2_RegnPlacement : public SimulationType {
  public:
    Simulation_NSGA2_RegnPlacement();

  private:
    static unsigned int RegnMax;

    class Individual : public NSGA_II::NSGA2_Individual {
        friend class Simulation_NSGA2_RegnPlacement;

      public:
        Individual(Simulation_NSGA2_RegnPlacement &Sim) : Sim(Sim) {}
        void createIndividual();
        int createGene(unsigned int i);

      private:
        Simulation_NSGA2_RegnPlacement &Sim;
    };

};


#endif // SIMULATION_NSGA2_REGENERATORPLACEMENT_H
