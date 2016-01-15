#ifndef CNORMNOISE_H
#define CNORMNOISE_H

#include "Cost.h"
#include <GeneralClasses/TransmissionBitrate.h>
#include <GeneralClasses/ModulationScheme.h>
#include <map>

namespace PSR
{

class cNormNoise : public Cost
{
public:
    cNormNoise(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);

private:
    struct CallProperties
    {
        std::weak_ptr<Link> link;
        TransmissionBitrate bitrate;
        ModulationScheme scheme;

        bool operator <(const CallProperties &other) const
        {
            return ((bitrate < other.bitrate) ||
                    ((bitrate == other.bitrate) && (scheme < other.scheme)) ||
                    ((bitrate == other.bitrate) && (scheme == other.scheme) &&
                     (link.lock() < other.link.lock())));
        }
    };

    void createCache();
    std::map <CallProperties, arma::rowvec> cache;
};

}

#endif // CNORMNOISE_H
