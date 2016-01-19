#include "GeneralClasses.h"
#include "Devices.h"
#include "Structure.h"
#include "Calls.h"
#include "RWA.h"
#include "SimulationTypes.h"
bool parallelism_enabled = true;

int main(void)
{
    std::cout << "\t* * * SIMULATOR OF SLICE OPTICAL NETWORKS * * *"
              << std::endl << std::endl;

    int startOption;
    std::cout << "Dear user, do you wish to: " << std::endl << "(1) Load a previous simulation;"
              << std::endl << "(2) Start a new simulation." << std::endl << "Enter: ";

    do
        {
        std::cin >> startOption;

        if (std::cin.fail() || startOption < 1 || startOption > 2)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid option." << std::endl << std::endl;
            std::cout << "Dear user, do you wish to: " << std::endl << "(1) Load a previous simulation;"
                      << std::endl << "(2) Start a new simulation." << std::endl << "Enter: ";
            }
        else
            {
            break;
            }
        }
    while (1);

    if(startOption == 2)
    {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "\t* * * SIMULATOR OF SLICE OPTICAL NETWORKS * * *"
                  << std::endl;
        auto simulation = SimulationType::create();
        simulation->print();
    }

    return 0;
}
