#ifndef BITRATE_H
#define BITRATE_H

#include "Cost.h"
#include <map>
#include <GeneralClasses/TransmissionBitrate.h>

namespace RMSA
{
namespace ROUT
{
namespace PSR
{

/**
 * @brief The cBitrate class has, as cost, the bitrate of the call, normalized
 * by the greatest bitrate possible.
 */
class cBitrate : public Cost
{
public:
    /**
     * @brief cBitrate is the standard constructor for the cBitrate cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     */
    cBitrate(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link>, std::shared_ptr<Call> C);

private:
    void createCache();
    std::map<TransmissionBitrate, arma::rowvec> cache;
};

}
}
}

#endif // BITRATE_H
