#include "include/RMSA/SpectrumAssignmentAlgorithms/FFE/FirstFitEvolutionary.h"
#include <Structure/Topology.h>
#include <Calls/Call.h>
#include <Structure/Link.h>
#include <Structure/Slot.h>
#include <algorithm>
#include <boost/program_options.hpp>

using namespace RMSA::SA;
using namespace RMSA::SA::FFE;

bool FirstFitEvolutionary::hasLoaded = false;
std::vector<int> FirstFitEvolutionary::defaultSlotsList(Link::NumSlots);

FirstFitEvolutionary::FirstFitEvolutionary(std::shared_ptr<Topology> T) :
    SpectrumAssignmentAlgorithm(T, FFE), hasSetSlots(false)
{
    if (hasLoaded)
        {
        slotsList = defaultSlotsList;
        hasSetSlots = true;
        }
}

void FirstFitEvolutionary::save(std::string filename)
{
    SpectrumAssignmentAlgorithm::save(filename);
}

std::map<std::weak_ptr<Link>,
    std::vector<std::weak_ptr<Slot>>,
    std::owner_less<std::weak_ptr<Link>>>
    FirstFitEvolutionary::assignSlots
    (std::shared_ptr<Call> C, TransparentSegment Seg)
{
    //initialization
    if (!hasSetSlots)
        {
        if (!hasLoaded)
            {
            load();
            }
        slotsList = defaultSlotsList;
        hasSetSlots = true;
        }

    int RequiredSlots = Seg.ModScheme.get_NumSlots(C->Bitrate);
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;
    Slots.clear();

    bool SlotsAvailability[Link::NumSlots];
    for (int i = 0; i < Link::NumSlots; i++)
        {
        SlotsAvailability[i] = true;
        }

    for (auto &link : Seg.Links)
        {
        auto locklink = link.lock();

        for (auto &slot : locklink->Slots)
            {
            SlotsAvailability[slot->numSlot] &= slot->isFree;
            }
        }

    for (auto si : slotsList)
        {
        if (si + RequiredSlots - 1 >= Link::NumSlots)
            {
            continue;
            }

        bool freeSlots = true;
        for (int s = si; (s < si + RequiredSlots) && freeSlots; ++s)
            {
            freeSlots &= SlotsAvailability[s];
            }

        if (freeSlots)
            {
            for (auto &link : Seg.Links)
                {
                Slots.emplace(link, std::vector<std::weak_ptr<Slot>>
                              (link.lock()->Slots.begin() + si,
                               link.lock()->Slots.begin() + si + RequiredSlots));
                }
            break;
            }
        }

    return Slots;
}

void FirstFitEvolutionary::setSlotsList(std::vector<int> newSlotsList)
{
    BOOST_ASSERT_MSG(newSlotsList.size() == slotsList.size(),
                     "Invalid slots list to FFE algorithm.");
    slotsList = newSlotsList;
}

void FirstFitEvolutionary::setDefaultSlotsList(std::vector<int> newSlotsList)
{
    defaultSlotsList = newSlotsList;
    hasLoaded = true;
}

void FirstFitEvolutionary::load()
{
    if (hasLoaded)
        {
        return;
        }

    std::string filename;

    std::cout << std::endl << "-> Define the FFE Slots List filepath." <<
              std::endl;
    do
        {
        std::cin >> filename;

        if (std::cin.fail() || !initDefaultList(filename))
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid list." << std::endl;
            std::cout << std::endl << "-> Define the FFE Slots List filepath." <<
                      std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    hasLoaded = true;
}

bool FirstFitEvolutionary::initDefaultList(std::string Filename)
{
    using namespace boost::program_options;

        {
        std::ifstream File(Filename);

        if (!File.is_open())
            {
            std::cerr << "Could not find file." << std::endl;
            return false;
            }
        }

    defaultSlotsList.clear();

    options_description FFEDescription("FFE");
    FFEDescription.add_options()
    ("FFE.value", value<double>(), "Minimum Achieved Blocking Probability")
    ("FFE.slotsorder", value<std::string>(), "Slots List");

    variables_map VariablesMap;

    store(parse_config_file<char>(Filename.c_str(), FFEDescription, true),
          VariablesMap);

    //Reads the FFE slot list
        {
        std::istringstream FFEList(
            VariablesMap.find("FFE.slotsorder")->second.as<std::string>());
        int currentslot;

        while (FFEList >> currentslot)
            {
            defaultSlotsList.push_back(currentslot);
            }
        }

    return true;
}
