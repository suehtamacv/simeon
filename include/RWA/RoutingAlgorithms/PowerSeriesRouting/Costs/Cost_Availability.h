#ifndef COST_AVAILABILITY
#define COST_AVAILABILITY

#include "Cost.h"

namespace PSR {

    class Availability : public Cost {
      public:
        Availability(int NMin, int NMax);
        arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call>);

      private:
        void createCache();
        arma::mat cache;
    };

}

#endif // COST_AVAILABILITY

