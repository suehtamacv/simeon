#include <RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h>
#include <Structure/Topology.h>

unsigned NX_RegeneratorPlacement::NX_N;
unsigned NX_RegeneratorPlacement::NX_X;

NX_RegeneratorPlacement::NX_RegeneratorPlacement(std::shared_ptr<Topology> T) :
    RegeneratorPlacementAlgorithm(T) {

}

void NX_RegeneratorPlacement::load() {
    std::cout << std::endl << "-> Define the number of translucent nodes."
              << std::endl;

    do {
        unsigned N;
        std::cin >> N;

        if (std::cin.fail() || N < 1 || N > T->Nodes.size()) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of translucent nodes." << std::endl;
            std::cout << std::endl << "-> Define the number of translucent nodes."
                      << std::endl;
        } else {
            NX_N = N;
            break;
        }
    } while (1);

    std::cout << std::endl << "-> Define the number of regenerators per node."
              << std::endl;

    do {
        unsigned X;
        std::cin >> X;

        if (std::cin.fail() || X < 1) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of regenerators per node." << std::endl;
            std::cout << std::endl << "-> Define the number of regenerators per node."
                      << std::endl;
        } else {
            NX_X = X;
            break;
        }
    } while (1);
}
