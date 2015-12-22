#ifndef COST_AVAILABILITY
#define COST_AVAILABILITY

#include "Cost.h"

namespace PSR {

    /**
    * @brief The Availability class has, as cost, the number of free slots on
    * each link, normalized by the number of slots on each link.
    */
    class Availability : public Cost {
      public:
        Availability(int NMin, int NMax, std::shared_ptr<Topology> T);
        arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call>);

      private:
        void createCache();
        arma::mat cache;
    };

}

#endif // COST_AVAILABILITY

