#ifndef FIRSTLONGESTREACH_H
#define FIRSTLONGESTREACH_H

#include <RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>
#include <GeneralClasses/ModulationScheme.h>

class FirstLongestReach : public RegeneratorAssignmentAlgorithm {
  public:
    FirstLongestReach(std::shared_ptr<Topology> T,
                      std::vector<ModulationScheme> ModulationSchemes);

    std::vector<TransparentSegment> assignRegenerators(
        std::shared_ptr<Call> C,
        std::vector<std::weak_ptr<Link> > Links);
};

#endif // FIRSTLONGESTREACH_H
