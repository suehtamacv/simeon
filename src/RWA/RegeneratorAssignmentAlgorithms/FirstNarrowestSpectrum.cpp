#include <algorithm>
#include <RWA/RegeneratorAssignmentAlgorithms/FirstNarrowestSpectrum.h>
#include <Structure/Link.h>
#include <Structure/Node.h>
#include <Calls/Call.h>
#include <RWA/TransparentSegment.h>

FirstNarrowestSpectrum::FirstNarrowestSpectrum(std::shared_ptr<Topology> T,
        std::vector<ModulationScheme> Schemes) :
    RegeneratorAssignmentAlgorithm(T, Schemes, RegeneratorAssignmentAlgorithms::FNS)
{

    //Sort schemes in decrescent order
    std::sort(ModulationSchemes.rbegin(), ModulationSchemes.rend());

}

std::vector<TransparentSegment> FirstNarrowestSpectrum::assignRegenerators(
    std::shared_ptr<Call> C,
    std::vector<std::weak_ptr<Link> > Links)
{

    unsigned int NeededRegenerators = get_NumNeededRegenerators(C);
    auto scheme = ModulationSchemes.begin();
    std::vector<TransparentSegment> TransparentSegments;
    std::vector<std::weak_ptr<Node>> Nodes;

    for (auto &link : Links)
        {
        Nodes.push_back(link.lock()->Origin);
        }

    Nodes.push_back(Links.back().lock()->Destination);

    auto r = Nodes.begin();

    for (auto s = Nodes.begin(); s != Nodes.end(); ++s)
        {
        for (auto x = s + 1; x != Nodes.end(); ++x)
            {
            if (((*x).lock()->get_NumAvailableRegenerators() >= NeededRegenerators) ||
                    ((*x).lock() == C->Destination.lock()))
                {

                if (isThereSpectrumAndOSNR(C, Links, *s, *x, *scheme))
                    {
                    if ((*x).lock() == C->Destination.lock())
                        {
                        TransparentSegments.push_back(
                            createTransparentSegment(C, Links, *s, *x, 0));
                        return TransparentSegments;
                        }
                    else
                        {
                        if (scheme != ModulationSchemes.begin())
                            {
                            TransparentSegments.push_back(
                                createTransparentSegment(C, Links, *s, *x, NeededRegenerators));
                            s = x;
                            r = x;
                            scheme = ModulationSchemes.begin();
                            }
                        else
                            {
                            r = x;
                            }
                        }
                    }
                else
                    {
                    if (r != s)
                        {
                        TransparentSegments.push_back(
                            createTransparentSegment(C, Links, *s, *r, NeededRegenerators));
                        s = r;
                        x = r;
                        }
                    else
                        {
                        --x;
                        ++scheme;

                        if (scheme == ModulationSchemes.end())
                            {
                            TransparentSegments.clear();
                            return TransparentSegments;
                            }
                        }
                    }

                }
            }
        }

    TransparentSegments.clear();
    return TransparentSegments;

}

void FirstNarrowestSpectrum::save(std::string SimConfigFileName)
{
    RegeneratorAssignmentAlgorithm::save(SimConfigFileName);
}
