#include "include/GeneralPurposeAlgorithms/GA/GA.h"

using namespace GeneticAlgorithm;

GA::GA()
{

}

void GA::run_Generation()
{
    if (evolution.empty())
        {
        createInitialGeneration();
        }
}
