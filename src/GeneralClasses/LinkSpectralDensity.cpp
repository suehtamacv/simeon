#include <GeneralClasses/LinkSpectralDensity.h>

#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <GeneralClasses/PhysicalConstants.h>
#include <GeneralPurposeAlgorithms/IntegrationMethods/TrapezoidalRule.h>

unsigned long LinkSpectralDensity::numFrequencySamples =
    Slot::numFrequencySamplesPerSlot * Link::NumSlots;

LinkSpectralDensity::LinkSpectralDensity(std::vector<std::shared_ptr<Slot>>
        LinkSlots) : LinkSlots(LinkSlots)
{
    for(auto& slot : LinkSlots)
        {
        S.push_back(slot->S);
        }
}

void LinkSpectralDensity::updateLink(SpectralDensity thisSpecDensity,std::vector<std::weak_ptr<Slot>> Slots)
{
    unsigned int firstSlot = Slots.front().lock()->numSlot;
    unsigned int lastSlot = Slots.back().lock()->numSlot;

    unsigned int k = 0;
    for(unsigned int i = firstSlot; i <= lastSlot; i++)
    {
        for(unsigned int j = 0; j < Slot::numFrequencySamplesPerSlot; j++)
        {
            //Erro no acesso a thisSpecDensity, em especial há uma divergência no tamanho dos slots
            //S.at(i)->specDensity(j) = thisSpecDensity.specDensity(k);
            k++;
        }        
        LinkSlots.at(i)->S = S.at(i);
    }
    // Teste
    /*
    if(k == thisSpecDensity.specDensity.n_cols)
        std::cout << std::endl << "OK" << std::endl;
    else
        std::cout << std::endl << "k = " << lastSlot - firstSlot + 1 << " ; Spec = " << thisSpecDensity.specDensity.n_cols/25 << std::endl;
        //std::cout << std::endl << "slots = " << firstSlot << " - " << lastSlot << std::endl;
    */
    // Teste
}
