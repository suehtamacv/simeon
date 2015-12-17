#include <RWA/RegeneratorPlacementAlgorithms/NX_RegeneratorPlacement.h>

NX_RegeneratorPlacement::NX_RegeneratorPlacement(std::shared_ptr<Topology> T) :
    RegeneratorPlacementAlgorithm(T) {

}

void NX_RegeneratorPlacement::load() {
    std::cout << "Enter with the number of translucent nodes." << std::endl;

    int N;

    do {        
        std::cin >> N;

        if(std::cin.fail() || N < 1) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number." << std::endl << std::endl;
            std::cout << "Enter with the number of translucent nodes." << std::endl;
        }
        else
            break;

    } while(1);

    std::cout << "Enter with the number of regenerators per node." << std::endl;

    int X;

    do {
        std::cin >> X;

        if(std::cin.fail() || X < 1 || N < X) {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number." << std::endl << std::endl;
            std::cout << "Enter with the number of regenerators per node." << std::endl;
        }
        else
            break;
    } while(1);

    placeRegenerators(N, X);
}
