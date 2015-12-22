#include <RWA/RoutingAlgorithms/PowerSeriesRouting/PowerSeriesRouting.h>
#include <iostream>
#include <algorithm>

PowerSeriesRouting::PowerSeriesRouting(std::shared_ptr<Topology> T) :
    DijkstraRoutingAlgorithm(T) {
    firstTimeRun = false;
    hasLoaded = false;
}

PowerSeriesRouting::PowerSeriesRouting(std::shared_ptr<Topology> T,
                                       std::vector<std::shared_ptr<PSR::Cost>> Costs) :
    DijkstraRoutingAlgorithm(T) {

    firstTimeRun = false;
    hasLoaded = true;

    NMin = Costs.front()->get_NMin();
    NMax = Costs.front()->get_NMax();

    //Copies the costs types, but not the costs themselves.
    //It's therefore topology-independent.
    for (auto cost : Costs) {
        this->Costs.push_back(PSR::Cost::createCost(cost->Type, NMin, NMax, T));
    }
}

long double PowerSeriesRouting::get_Cost(std::weak_ptr<Link> link,
        std::shared_ptr<Call> C) {
    arma::mat cost_matrix = arma::ones(1);

    for (auto cost : Costs) {
        cost_matrix = arma::kron(cost_matrix, cost->getCost(link, C));
    }

    if (!firstTimeRun) {
        coefficients.copy_size(cost_matrix);
        firstTimeRun = true;
    }

    return arma::accu(coefficients % cost_matrix);
}

void PowerSeriesRouting::load() {
    if (hasLoaded) {
        return;
    }

    std::cout << std::endl << "-> Define the minimum exponent." << std::endl;

    do {
        int nmin;
        std::cin >> nmin;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid minimum exponent." << std::endl;
            std::cout << std::endl << "-> Define the minimum exponent." << std::endl;
        } else {
            NMin = nmin;
            break;
        }
    } while (1);

    std::cout << std::endl << "-> Define the maximum exponent." << std::endl;

    do {
        int nmax;
        std::cin >> nmax;

        if (std::cin.fail() || nmax < NMin) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid maximum exponent." << std::endl;
            std::cout << std::endl << "-> Define the maximum exponent." << std::endl;
        } else {
            NMax = nmax;
            break;
        }
    } while (1);

    std::cout << std::endl << "-> Choose the PSR Costs." << std::endl;

    do {
        std::vector<PSR::Cost::PossibleCosts> chosenCosts;

        do {
            int numPossibleCosts = 0;

            for (auto cost : PSR::Cost::CostsNames.left) {
                if (std::find(chosenCosts.begin(), chosenCosts.end(),
                              cost.first) != chosenCosts.end()) {
                    continue;
                } //Verifies whether the cost has already been chosen.

                std::cout << "(" << cost.first << ")\t" << cost.second << std::endl;
                numPossibleCosts++;
            }

            if (numPossibleCosts == 0) {
                break;
            }

            int Cost;
            std::cin >> Cost;

            if (std::cin.fail() ||
                    PSR::Cost::CostsNames.left.count((PSR::Cost::PossibleCosts) Cost) == 0) {
                std::cin.clear();
                std::cin.ignore();

                if (Cost == -1 && !chosenCosts.empty()) {
                    break;
                }

                std::cerr << "Invalid Cost." << std::endl;
            } else if (std::find(chosenCosts.begin(), chosenCosts.end(),
                                 (PSR::Cost::PossibleCosts) Cost) == chosenCosts.end()) {
                chosenCosts.push_back((PSR::Cost::PossibleCosts) Cost);
                Costs.push_back(PSR::Cost::createCost(
                                    (PSR::Cost::PossibleCosts) Cost, NMin, NMax, T));
            } //Verifies that the cost hasn't been chosen.

            std::cout << std::endl << "-> Choose the PSR Costs. (-1 to exit)" << std::endl;
        } while (1);

    } while (0); //Dummy do-while. Only to encapsulate reading.

    hasLoaded = true;
}

void PowerSeriesRouting::initCoefficients(PSO::PSO_Particle<double> particle) {
    coefficients = arma::mat(particle.X);
}

std::vector<std::shared_ptr<PSR::Cost>> PowerSeriesRouting::get_Costs() {
    return Costs;
}
