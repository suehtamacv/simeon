#ifndef FIRSTLONGESTREACH_H
#define FIRSTLONGESTREACH_H

#include <RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>
#include <GeneralClasses/ModulationScheme.h>

/**
 * @brief The FirstLongestReach class implements the First Longest Reach
 * RegeneratorAssignmentAlgorithm.
 *
 * This algorithm tries to perform the regeneration (if it is needed) as far as
 * possible from the source node.
 */
class FirstLongestReach : public RegeneratorAssignmentAlgorithm {
  public:
    /**
     * @brief FirstLongestReach is the standard constructor.
     * @param T is a pointer to the Topology.
     * @param ModulationSchemes is a vector containing the possible ModulationScheme.
     */
    FirstLongestReach(std::shared_ptr<Topology> T,
                      std::vector<ModulationScheme> ModulationSchemes);

    std::vector<TransparentSegment> assignRegenerators(
        std::shared_ptr<Call> C,
        std::vector<std::weak_ptr<Link> > Links);
};

#endif // FIRSTLONGESTREACH_H
