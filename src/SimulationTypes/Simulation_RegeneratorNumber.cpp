#include <SimulationTypes/Simulation_RegeneratorNumber.h>
#include <Structure/Link.h>
#include <Calls/CallGenerator.h>

Simulation_RegeneratorNumber::Simulation_RegeneratorNumber() :
    hasLoaded(false)
{

}

void Simulation_RegeneratorNumber::help()
{
    std::cout << "\t\tNUMBER OF REGENERATORS" << std::endl << std::endl <<
              "This simulation inserts regenerators in the nodes of the "
              " topology, and analyses the call requisition blocking probability."
              " If the RP Algorithm is NX, then the same number of regenerators"
              " will be inserted in each node. Otherwise, the product N . X is"
              " distributed over the topology." << std::endl;
}

void Simulation_RegeneratorNumber::run()
{
    if (!hasLoaded)
        {
        load();
        }

    extern bool parallelism_enabled;
    #pragma omp parallel for ordered schedule(dynamic) if(parallelism_enabled)

    for (unsigned i = 0; i < simulations.size(); i++)
        {
        if (!simulations[i]->hasSimulated)
            {
            simulations[i]->run();
            }
        }
}

void Simulation_RegeneratorNumber::load()
{
    //General readings
    SimulationType::load();

    Node::load();

    Link::load(T);

    //RWA Algorithms
        {
        //Routing Algorithm
        Routing_Algorithm = RoutingAlgorithm::define_RoutingAlgorithm();

        //Wavelength Assignment Algorithm
        WavAssign_Algorithm =
            WavelengthAssignmentAlgorithm::define_WavelengthAssignmentAlgorithm();

        //Regenerator Placement Algorithm
        RegPlacement_Algorithm =
            RegeneratorPlacementAlgorithm::define_RegeneratorPlacementAlgorithm();

        //Regenerator Assignment Algorithm
        RegAssignment_Algorithm =
            RegeneratorAssignmentAlgorithm::define_RegeneratorAssignmentAlgorithm();
        }

    std::cout << std::endl << "-> Define the number of calls." << std::endl;

    do
        {
        std::cin >> NumCalls;

        if (std::cin.fail() || NumCalls < 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of calls." << std::endl;
            std::cout << std::endl << "-> Define the number of calls." << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the network load." << std::endl;

    do
        {
        std::cin >> OptimizationLoad;

        if (std::cin.fail() || OptimizationLoad < 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid network load." << std::endl;
            std::cout << std::endl << "-> Define the network load." << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl <<
              "-> Define the minimum number of regenerators per node"
              << std::endl;

    do
        {
        std::cin >> minRegNumber;

        if (std::cin.fail())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of regenerators." << std::endl;
            std::cout << std::endl <<
                      "-> Define the minimum number of regenerators per node"
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl <<
              "-> Define the maximum number of regenerators per node"
              << std::endl;

    do
        {
        std::cin >> maxRegNumber;

        if (std::cin.fail() || maxRegNumber < minRegNumber)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of regenerators." << std::endl;
            std::cout << std::endl <<
                      "-> Define the maximum number of regenerators per node"
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the number of regenerators per node step"
              << std::endl;

    do
        {
        std::cin >> stepRegNumber;

        if (std::cin.fail())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of regenerators." << std::endl;
            std::cout << std::endl << "-> Define the number of regenerators per node step"
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the number of translucent nodes"
              << std::endl;

    do
        {
        std::cin >> numTranslucentNodes;

        if (std::cin.fail() || numTranslucentNodes > T->Nodes.size())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid number of translucent nodes."  << std::endl;
            std::cout << std::endl << "-> Define the number of translucent nodes"
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    createSimulations();

    hasLoaded = true;
}

void Simulation_RegeneratorNumber::save(std::string SimConfigFileName)
{
    std::ofstream SimConfigFile("SimConfigFile.txt",
                               std::ofstream::out | std::ofstream::trunc);

    BOOST_ASSERT_MSG(SimConfigFile.is_open(), "Output file is not open");

    SimConfigFile << "\t* * * ADAMANT BROCCOLI SIMULATOR OF SLICE OPTICAL NETWORKS * * *" << std::endl << std::endl;
    SimConfigFile << "Simulation Configurations File:" << std::endl << std::endl;
    SimConfigFile << "PARAMETER = VALUE" << std::endl;

    SimConfigFile << "simulation = regnum" << std::endl;
    SimConfigFile << "avgspanlength = " << T->AvgSpanLength << std::endl;
    SimConfigFile << "routalg = " << RoutingAlgorithm::RoutingAlgorithmNicknames.left.at(Routing_Algorithm) << std::endl;
    SimConfigFile << "waa = " << WavelengthAssignmentAlgorithm::WavelengthAssignmentAlgorithmNicknames.left.at(WavAssign_Algorithm) << std::endl;
    //SimConfigFile << "rpa = " << RegeneratorPlacementAlgorithm::RegeneratorPlacementNicknames.left.at(RegAssignment_Algorithm) << std::endl;
    //SimConfigFile << "raa = " << RegeneratorAssignmentAlgorithm::RegeneratorAssignmentNicknames.left.at(RegPlacement_Algorithm) << std::endl;
    SimConfigFile << "callnum = " << NumCalls << std::endl;
    SimConfigFile << "netload = " << OptimizationLoad << std::endl;
    SimConfigFile << "minregnum = " << minRegNumber << std::endl;
    SimConfigFile << "maxregnum = " << maxRegNumber << std::endl;
    SimConfigFile << "regstep = " << stepRegNumber << std::endl;
    SimConfigFile << "translnodes = " << numTranslucentNodes << std::endl;

    SimConfigFile << std::endl << "Topology Data:" << std::endl << std::endl;
    T->save("SimConfigFile.txt");
}

void Simulation_RegeneratorNumber::load_file(std::string)
{

}

void Simulation_RegeneratorNumber::print()
{
    if (!hasLoaded)
        {
        load();
        }

    std::cout << std::endl << "* * RESULTS * *" << std::endl;
    std::cout << "NUM REGENERATORS\tCALL BLOCKING PROBABILITY" << std::endl;

    extern bool parallelism_enabled;
    #pragma omp parallel for ordered schedule(dynamic) if(parallelism_enabled)

    for (unsigned i = 0; i < simulations.size(); i++)
        {
        if (!simulations[i]->hasSimulated)
            {
            simulations[i]->run();
            }

        #pragma omp ordered
        std::cout << simulations[i]->Generator->T->get_NumRegenerators() << "\t\t\t"
                  << simulations[i]->get_CallBlockingProbability() << std::endl;

        }

    char saveOption;
    std::cout << std::endl << "Do you wish to save the configurations of this simulation (y/n)? ";
    std::cin >> saveOption;
    /*
    if(saveOption == 'y' || saveOption == 'Y') {
        std::string saveFileName;
        std::cout << "Enter the file name: ";
        saveFileName.append(".txt");
        std::getline(std::cin, saveFileName);
        save(saveFileName);
    } */
    save("");
}

void Simulation_RegeneratorNumber::createSimulations()
{
    placeRegenerators(T);

    for (unsigned long nreg = minRegNumber; nreg <= maxRegNumber;
            nreg += stepRegNumber)
        {
        //Creates a copy of the Topology
        std::shared_ptr<Topology> TopologyCopy(new Topology(*T));

        //Reallocates the regenerators
        refreshRegenerators(TopologyCopy, nreg * numTranslucentNodes);

        //Creates the RWA Algorithms
        std::shared_ptr<RoutingAlgorithm> R_Alg =
            RoutingAlgorithm::create_RoutingAlgorithm(Routing_Algorithm, TopologyCopy);

        std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg =
            WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
                WavAssign_Algorithm, TopologyCopy);

        std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg =
            RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
                RegAssignment_Algorithm, TopologyCopy);

        //Creates the Call Generator and the RWA Object
        std::shared_ptr<CallGenerator> Generator(new CallGenerator(TopologyCopy,
                OptimizationLoad));
        std::shared_ptr<RoutingWavelengthAssignment> RWA(
            new RoutingWavelengthAssignment(
                R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, TopologyCopy));

        //Push simulation into stack
        simulations.push_back(
            std::shared_ptr<NetworkSimulation>(new NetworkSimulation(
                    Generator, RWA, NumCalls)));
        }
}

void Simulation_RegeneratorNumber::placeRegenerators(
    std::shared_ptr<Topology> Top)
{
    std::shared_ptr<RoutingAlgorithm> R_Alg =
        RoutingAlgorithm::create_RoutingAlgorithm(
            Routing_Algorithm, Top);
    std::shared_ptr<WavelengthAssignmentAlgorithm> WA_Alg =
        WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
            WavAssign_Algorithm, Top);
    std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg =
        RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
            RegAssignment_Algorithm, Top);
    std::shared_ptr<RoutingWavelengthAssignment> RWA(
        new RoutingWavelengthAssignment(
            R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, Top));

    std::shared_ptr<RegeneratorPlacementAlgorithm> RP_Alg =
        RegeneratorPlacementAlgorithm::create_RegeneratorPlacementAlgorithm(
            RegPlacement_Algorithm, Top, RWA, OptimizationLoad, NumCalls, false);

    if (RP_Alg->isNXAlgorithm)
        {
        RP_Alg->placeRegenerators(numTranslucentNodes, 100);
        }
    else
        {
        RP_Alg->placeRegenerators(numTranslucentNodes * 100);
        }
}

void Simulation_RegeneratorNumber::refreshRegenerators(
    std::shared_ptr<Topology> Top, unsigned long numReg)
{
    unsigned long totalReg = Top->get_NumRegenerators();

    for (auto &node : Top->Nodes)
        {
        unsigned long nodeNumReg = node->get_NumRegenerators();

        if (nodeNumReg != 0)
            {
            node->set_NumRegenerators(std::round(nodeNumReg * numReg / (1.0 * totalReg)));
            }
        }
}
