#ifndef FIRSTNARROWESTSPECTRUM_H
#define FIRSTNARROWESTSPECTRUM_H

#include <RWA/RegeneratorAssignmentAlgorithms/RegeneratorAssignmentAlgorithm.h>

/**
 * @brief The FirstNarrowestSpectrum class implements the First Narrowest Spectrum
 * RegeneratorAssignmentAlgorithm.
 *
 * The algorithm tries to save spectrum in the network by always trying to use
 * the highest allowed spectral efficiency modulation format in the TransparentSegment.
 */
class FirstNarrowestSpectrum : public RegeneratorAssignmentAlgorithm
{
public:
    /**
     * @brief FirstNarrowestSpectrum is the standard constructor.
     * @param T is a pointer to the Topology.
     * @param Schemes is a vector containing the possible ModulationScheme.
     */
    FirstNarrowestSpectrum(std::shared_ptr<Topology> T,
                           std::vector<ModulationScheme> Schemes);
    std::vector<TransparentSegment> assignRegenerators(
        std::shared_ptr<Call> C,
        std::vector<std::weak_ptr<Link>> Links);
    void load() {}
};

#endif // FIRSTNARROWESTSPECTRUM_H
