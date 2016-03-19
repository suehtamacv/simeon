#include "include/SimulationTypes/Simulation_NSGA2_RegnPlac/NSGA2_Parameter_CapEx.h"

using namespace Simulations::NSGA2_Parameters;

NSGA2_Parameter_CapEx::NSGA2_Parameter_CapEx
(std::vector<int> gene, Simulation_NSGA2_RegnPlac &Sim) :
    NSGA2_Parameter(gene), Sim(Sim)
{

}

double NSGA2_Parameter_CapEx::evaluate()
{
    if (!isEvaluated)
        {
        Topology T(*Sim.T);

        for (unsigned int i = 0; i < gene.size(); i++)
            {
            if (gene[i] != 0)
                {
                T.Nodes[i]->set_NodeType(Node::TranslucentNode);
                }
            else
                {
                T.Nodes[i]->set_NodeType(Node::TransparentNode);
                }

            T.Nodes[i]->set_NumRegenerators(gene[i]);
            }

        CapEx = T.get_CapEx();
        isEvaluated = true;
        }

    return CapEx;
}
