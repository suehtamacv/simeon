#ifndef COST_NORMALIZEDCONTIGUITY_H
#define COST_NORMALIZEDCONTIGUITY_H

#include "Cost.h"

namespace PSR {

    /**
    * @brief The cNormContiguity class has, as cost, the contiguity
    * measure of the link. It only works on transparent networks. If sr is the
    * number of possible allocations of the call C in the Link link, then this
    * cost is sr / SR.
    */
    class cNormContiguity : public Cost {
      public:
        cNormContiguity(int NMin, int NMax, std::shared_ptr<Topology> T);
        arma::rowvec getCost(std::weak_ptr<Link> link, std::shared_ptr<Call> C);

      private:
        void createCache();
        arma::mat cache;
    };

}

#endif // COST_NORMALIZEDCONTIGUITY_H

