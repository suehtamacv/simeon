#ifndef CMODULATIONSCHEME_H
#define CMODULATIONSCHEME_H

#include "Cost.h"
#include <map>
#include <GeneralClasses/ModulationScheme.h>

namespace PSR {

    class cModulationScheme : public Cost {
      public:
        cModulationScheme(int NMin, int NMax, std::shared_ptr<Topology> T);
        arma::rowvec getCost(std::weak_ptr<Link>, std::shared_ptr<Call>);

      private:
        void createCache();
        std::map<ModulationScheme, arma::rowvec> cache;
    };

}

#endif // CMODULATIONSCHEME_H
