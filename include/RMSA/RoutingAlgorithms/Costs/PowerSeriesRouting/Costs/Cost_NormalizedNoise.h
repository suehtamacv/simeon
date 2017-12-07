#ifndef COST_NORMALIZEDNOISE_H
#define COST_NORMALIZEDNOISE_H

#include "Cost.h"
#include "GeneralClasses/TransmissionBitrate.h"
#include "GeneralClasses/ModulationScheme.h"
#include <map>

namespace RMSA
{
namespace ROUT
{
namespace PSR
{
class cNormNoise : public Cost
{
public:
    /**
     * @brief cNormNoise is the standard constructor for the cNormNoise cost.
     * @param NMin is the minimum exponent to the cost.
     * @param NMax is the maximum exponent to the cost.
     * @param T is the topology.
     */
    cNormNoise(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);
    double getUnitCost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);

private:
    struct CallProperties
    {
        int Origin;
        int Destination;
        TransmissionBitrate bitrate;
        ModulationScheme scheme;

        CallProperties(int Origin, int Destination,
                       TransmissionBitrate bitrate, ModulationScheme scheme) :
            Origin(Origin), Destination(Destination), bitrate(bitrate), scheme(scheme) {}

        bool operator <(const CallProperties &other) const
        {
            if (Origin < other.Origin)
                {
                return true;
                }
            else if (Origin == other.Origin)
                {
                if (Destination < other.Destination)
                    {
                    return true;
                    }
                else if (Destination == other.Destination)
                    {
                    if (bitrate < other.bitrate)
                        {
                        return true;
                        }
                    else if (bitrate == other.bitrate)
                        {
                        if (scheme < other.scheme)
                            {
                            return true;
                            }
                        else
                            {
                            return false;
                            }
                        }
                    }
                }
            return false;
        }
    };

    void createCache();
    std::map <CallProperties, arma::rowvec> cache;
    std::map <CallProperties, double> unitCache;
};
}
}
}

#endif // COST_NORMALIZEDNOISE_H
