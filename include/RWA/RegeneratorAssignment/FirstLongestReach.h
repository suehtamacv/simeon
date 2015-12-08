#ifndef FIRSTLONGESTREACH_H
#define FIRSTLONGESTREACH_H

#include <RWA/RegeneratorAssignment/RegeneratorAssignment.h>
#include <ModulationSchemes/M_QAM.h>

class FirstLongestReach : public RegeneratorAssignment {
  public:
    FirstLongestReach(std::shared_ptr<Topology> T,
                      std::vector<std::shared_ptr<M_QAM>> ModulationSchemes);

    bool assignRegenerators(Call C, std::shared_ptr<Route> R);

    std::vector<std::shared_ptr<M_QAM>> ModulationSchemes;

  private:
    bool isThereSpectrumAndOSNR(Call C,
                                std::shared_ptr<Route> R,
                                std::weak_ptr<Node> s,
                                std::weak_ptr<Node> x);
};

#endif // FIRSTLONGESTREACH_H
