#ifndef CMODULATIONSCHEME_H
#define CMODULATIONSCHEME_H

#include "Cost.h"
#include <map>
#include <GeneralClasses/ModulationScheme.h>

namespace ROUT
{
namespace PSR
{

/**
 * @brief The cModulationScheme class has, as cost, the modulation scheme used
 * by this connection, normalized by the greatest modulation scheme available.
 */
class cModulationScheme : public Cost
{
public:
    cModulationScheme(int NMin, int NMax, std::shared_ptr<Topology> T);
    arma::rowvec getCost(std::weak_ptr<Link>, std::shared_ptr<Call>);

private:
    void createCache();
    std::map<ModulationScheme, arma::rowvec> cache;
};

}
}

#endif // CMODULATIONSCHEME_H
