#include <algorithm>
#include <RMSA/RegeneratorAssignmentAlgorithms/FirstNarrowestSpectrum.h>
#include <Structure/Link.h>
#include <Structure/Node.h>
#include <Calls/Call.h>
#include <RMSA/TransparentSegment.h>

using namespace RMSA::RA;

FirstNarrowestSpectrum::FirstNarrowestSpectrum(std::shared_ptr<Topology> T,
        std::set<ModulationScheme> Schemes) :
    RegeneratorAssignmentAlgorithm(T, FNS, Schemes)
{

}

std::vector<RMSA::TransparentSegment>
FirstNarrowestSpectrum::assignRegenerators(
    std::shared_ptr<Call> C,
    std::vector<std::weak_ptr<Link> > Links)
{

    unsigned int NeededRegenerators = get_NumNeededRegenerators(C);
    auto scheme = ModulationSchemes.rbegin();
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
                        if (scheme != ModulationSchemes.rbegin())
                            {
                            TransparentSegments.push_back(
                                createTransparentSegment(C, Links, *s, *x, NeededRegenerators));
                            s = x;
                            r = x;
                            scheme = ModulationSchemes.rbegin();
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

                        if (scheme == ModulationSchemes.rend())
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
