#include "include/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_BlockingProbability.h"
#include "include/Calls/CallGenerator.h"
#include "include/RMSA/RoutingWavelengthAssignment.h"
#include "include/SimulationTypes/NetworkSimulation.h"

using namespace Simulations::NSGA2_Parameters;
using namespace RMSA;
using namespace ROUT;
using namespace SA;
using namespace RA;

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
            RoutingAlgorithm::create_RoutingAlgorithm(Sim.Routing_Algorithm,
                    Sim.Routing_Cost, T);
        std::shared_ptr<SpectrumAssignmentAlgorithm> WA_Alg =
            SA::SpectrumAssignmentAlgorithm::create_SpectrumAssignmentAlgorithm(
                Sim.WavAssign_Algorithm, T);
        std::shared_ptr<RegeneratorAssignmentAlgorithm> RA_Alg =
            RegeneratorAssignmentAlgorithm::create_RegeneratorAssignmentAlgorithm(
                Sim.RegAssignment_Algorithm, T);

        //Creates the Call Generator and the RMSA Object
        std::shared_ptr<CallGenerator> Generator(new CallGenerator(T,
                Sim.NetworkLoad));
        std::shared_ptr<RoutingWavelengthAssignment> RMSA(
            new RoutingWavelengthAssignment(
                R_Alg, WA_Alg, RA_Alg, ModulationScheme::DefaultSchemes, T));

        value = NetworkSimulation(Generator, RMSA, Sim.NumCalls)
                .get_CallBlockingProbability();
        isEvaluated = true;
        }

    return value;
}
