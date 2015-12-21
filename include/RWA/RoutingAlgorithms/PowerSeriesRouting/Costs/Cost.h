#ifndef COST_H
#define COST_H

#include <memory>
#include <armadillo>

class Link;
class Call;

namespace PSR {

    class Cost {
      public:
        Cost(int NMin, int NMax);
        virtual arma::rowvec getCost(std::weak_ptr<Link> link,
                                     std::shared_ptr<Call> C) = 0;

      protected:
        int NMin, NMax;
    };

}

#endif // COST_H
