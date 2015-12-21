#include <RWA/RoutingAlgorithms/PowerSeriesRouting/PowerSeriesRouting.h>

PowerSeriesRouting::PowerSeriesRouting(std::shared_ptr<Topology> T) :
    DijkstraRoutingAlgorithm(T) {

}

long double PowerSeriesRouting::get_Cost(std::weak_ptr<Link> link,
        std::shared_ptr<Call> C) {
    arma::mat cost_matrix = arma::ones(1);

    for (auto cost : Costs) {
        cost_matrix = arma::kron(cost_matrix, cost->getCost(link, C));
    }

    coefficients.resize(arma::size(cost_matrix));
    return arma::accu(coefficients % cost_matrix);
}

void PowerSeriesRouting::load() {

}
