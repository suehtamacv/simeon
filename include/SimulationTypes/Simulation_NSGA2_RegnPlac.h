#ifndef SIMULATION_NSGA2_REGENERATORPLACEMENT_H
#define SIMULATION_NSGA2_REGENERATORPLACEMENT_H

#include "SimulationType.h"
#include <GeneralPurposeAlgorithms/NSGA-2.h>

class Simulation_NSGA2_RegnPlac : public SimulationType {
  public:
    Simulation_NSGA2_RegnPlac();

    void help();
    void run();
    void load();
    void save(std::string);
    void load_file(std::string);
    void print();

  private:
    static unsigned int RegnMax;

    class Individual;

    class Param_BlockProb;
    class Param_CapEx;
    class Param_OpEx;

    class Sim_NSGA2;
};

class Simulation_NSGA2_RegnPlac::Individual : public NSGA2_Individual {
    friend class Simulation_NSGA2_RegnPlac;

  public:
    Individual(Simulation_NSGA2_RegnPlac &Sim) : Sim(Sim) {}
    void createIndividual();
    int createGene(unsigned int i);
    void setGene(std::vector<int> gene);
    std::shared_ptr<NSGA2_Individual> clone();

  private:
    Simulation_NSGA2_RegnPlac &Sim;
};

class Simulation_NSGA2_RegnPlac::Param_BlockProb : public NSGA2_Parameter {
    friend class Simulation_NSGA2_RegnPlac;

  public:
    Param_BlockProb(std::vector<int> gene, Simulation_NSGA2_RegnPlac &Sim);
    double evaluate();

  private:
    Simulation_NSGA2_RegnPlac &Sim;
};

class Simulation_NSGA2_RegnPlac::Param_CapEx : public NSGA2_Parameter {
    friend class Simulation_NSGA2_RegnPlac;

  public:
    Param_CapEx(std::vector<int> gene, Simulation_NSGA2_RegnPlac &Sim);
    double evaluate();

  private:
    Simulation_NSGA2_RegnPlac &Sim;
};

class Simulation_NSGA2_RegnPlac::Param_OpEx : public NSGA2_Parameter {
    friend class Simulation_NSGA2_RegnPlac;

  public:
    Param_OpEx(std::vector<int> gene, Simulation_NSGA2_RegnPlac &Sim);
    double evaluate();

  private:
    Simulation_NSGA2_RegnPlac &Sim;
};

class Simulation_NSGA2_RegnPlac::Sim_NSGA2 : public NSGA2 {
    friend class Simulation_NSGA2_RegnPlac;

  public:
    Sim_NSGA2(Simulation_NSGA2_RegnPlac &Sim);
    void createInitialGeneration();

  private:
    Simulation_NSGA2_RegnPlac &Sim;
};

#endif // SIMULATION_NSGA2_REGENERATORPLACEMENT_H
