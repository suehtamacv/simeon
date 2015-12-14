#ifndef FIRSTNARROWESTSPECTRUM_H
#define FIRSTNARROWESTSPECTRUM_H

#include <RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>

class FirstNarrowestSpectrum : public RegeneratorAssignmentAlgorithm {
  public:
    FirstNarrowestSpectrum(std::shared_ptr<Topology> T,
                           std::vector<ModulationScheme> Schemes);
    std::vector<TransparentSegment> assignRegenerators(
        std::shared_ptr<Call> C,
        std::vector<std::weak_ptr<Link>> Links);
};

#endif // FIRSTNARROWESTSPECTRUM_H
