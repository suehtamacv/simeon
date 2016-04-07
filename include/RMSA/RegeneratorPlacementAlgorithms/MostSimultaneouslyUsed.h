#ifndef MOSTSIMULTANEOUSLYUSED_H
#define MOSTSIMULTANEOUSLYUSED_H

#include <RMSA/RegeneratorPlacementAlgorithms/RegeneratorPlacementAlgorithm.h>
#include <GeneralClasses/TransmissionBitrate.h>

namespace RMSA
{
class RoutingWavelengthAssignment;

namespace RP
{
/**
 * @brief The MostSimultaneouslyUsed class represents the Most Simultaneously Used
 * RP algorithm.
 *
 * It runs an opaque simulation and computes the maximum amount of regenerators that
 * were simultaneously used on each node. Then it divides the regenerators proportionally
 * to this number.
 */
class MostSimultaneouslyUsed : public RegeneratorPlacementAlgorithm
{
public:
    /**
     * @brief MostSimultaneouslyUsed is the standard constructor.
     */
    MostSimultaneouslyUsed(std::shared_ptr<Topology> T,
                           std::shared_ptr<RoutingWavelengthAssignment> RMSA,
                           double NetworkLoad,
                           long long unsigned NumCalls = 1E6,
                           std::vector<TransmissionBitrate> Bitrates = TransmissionBitrate::DefaultBitrates
                          );
    /**
     * @brief placeRegenerators runs an opaque simulation and inserts NReg regenerators
     * distributed over the entire topology.
     *
     * Please note that MSU is not a NX Reg. Placement Algorithm. It's only parameter is
     * the number of regenerators, NumTotalReg, and not the N-X pair.
     *
     * @param NumTotalReg is the number of regenerators that will be distributed over the
     * topology.
     */
    void placeRegenerators(unsigned NumTotalReg = MSU_NumTotalReg, unsigned = 0);
    void load();

private:
    std::shared_ptr<RoutingWavelengthAssignment> RMSA;
    double NetworkLoad;
    long long unsigned NumCalls;
    std::vector<TransmissionBitrate> Bitrates;
    static unsigned MSU_NumTotalReg;

};
}
}

#endif // MOSTSIMULTANEOUSLYUSED_H
