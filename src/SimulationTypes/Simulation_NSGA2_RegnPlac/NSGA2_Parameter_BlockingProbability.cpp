#include "include/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_BlockingProbability.h"
#include "include/Calls/CallGenerator.h"
#include "include/RWA/RoutingWavelengthAssignment.h"
#include "include/SimulationTypes/NetworkSimulation.h"

using namespace Simulations::NSGA2_Parameters;

NSGA2_Parameter_BlockingProbability::NSGA2_Parameter_BlockingProbability(
    std::vector<int> gene, Simulation_NSGA2_RegnPlac &Sim) :
    NSGA2_Parameter(gene), Sim(Sim)
{

}

double NSGA2_Parameter_BlockingProbability::evaluate()
{
    if (!isEvaluated)
        {
        std::shared_ptr<Topology> T(new Topology(*Sim.T));

        for (unsigned int i = 0; i < gene.size(); i++)
            {
            if (gene[i] != 0)
                {
                T->Nodes[i]->set_NodeType(Node::TranslucentNode);
                }
            else
                {
                T->Nodes[i]->set_NodeType(Node::TransparentNode);
                }

            T->Nodes[i]->set_NumRegenerators(gene[i]);
            }

        std::shared_ptr<RoutingAlgorithm> R_Alg =
            RoutingAlgorithm::create_RoutingAlgorithm(Sim.Routing_Algorithm, T);
        std::shared_ptr<WA::WavelengthAssignmentAlgorithm> WA_Alg =
            WA::WavelengthAssignmentAlgorithm::create_WavelengthAssignmentAlgorithm(
                Sim.WavAssign_Algorithm, T);
        std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg =
            RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
                Sim.RegAssignment_Algorithm, T);

        //Creates the Call Generator and the RWA Object
        std::shared_ptr<CallGenerator> Generator(new CallGenerator(T,
                Sim.NetworkLoad));
        std::shared_ptr<RoutingWavelengthAssignment> RWA(
            new RoutingWavelengthAssignment(
                R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, T));

        value = NetworkSimulation(Generator, RWA, Sim.NumCalls)
                    .get_CallBlockingProbability();
        isEvaluated = true;
        }

    return value;
}
