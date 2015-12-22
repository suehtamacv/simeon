#ifndef COST_OCCUPABILITY_H
#define COST_OCCUPABILITY_H

#include "Cost.h"

namespace PSR {
    /**
    * @brief The Occupability class has, as cost, the number of occupied slots
    * on each link, normalized by the number of slots on each link.
    */
    class Occupability : public Cost {
      public:
        Occupability(int NMin, int NMax, std::shared_ptr<Topology> T);
        arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call>);

      private:
        void createCache();
        arma::mat cache;
    };

}

#endif // COST_OCCUPABILITY_H

