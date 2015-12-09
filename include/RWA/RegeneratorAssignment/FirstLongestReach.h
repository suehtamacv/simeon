#ifndef FIRSTLONGESTREACH_H
#define FIRSTLONGESTREACH_H

#include <RWA/RegeneratorAssignment/RegeneratorAssignment.h>
#include <ModulationSchemes/ModulationScheme.h>

class FirstLongestReach : public RegeneratorAssignment {
  public:
    FirstLongestReach(std::shared_ptr<Topology> T,
                      std::vector<std::shared_ptr<ModulationScheme>> ModulationSchemes);

    std::vector<TransparentSegment> assignRegenerators(Call C,
            std::vector<std::weak_ptr<Link> > Links);
};

#endif // FIRSTLONGESTREACH_H
