#include <SimulationTypes/Simulation_TransparencyAnalysis.h>
#include <RWA/RoutingAlgorithms/StaticRouting/ShortestPath.h>
#include <RWA/WavelengthAssignmentAlgorithms/FirstFit.h>
#include <RWA/RoutingWavelengthAssignment.h>
#include <RWA/Route.h>
#include <Structure/Link.h>
#include <Calls/Call.h>
#include <GeneralClasses/Signal.h>
#include <algorithm>

Simulation_TransparencyAnalysis::Simulation_TransparencyAnalysis()
{
    hasLoaded = hasRun = false;
    minModulationScheme =
        std::shared_ptr<ModulationScheme>(new ModulationScheme(*std::min_element(
                ModulationScheme::DefaultSchemes.begin(),
                ModulationScheme::DefaultSchemes.end())));

    maxBitrate =
        std::shared_ptr<TransmissionBitrate>(new TransmissionBitrate(*std::max_element(
                    TransmissionBitrate::DefaultBitrates.begin(),
                    TransmissionBitrate::DefaultBitrates.end())));
}

void Simulation_TransparencyAnalysis::help()
{
    std::cout << "\t\tTRANSPARENCY ANALYSIS" << std::endl << std::endl <<
              "This simulation varies the average distance between inline amplifiers "
              " and the input OSNR, and checks whether it's still possible to "
              " establish a connection in the route with longest length found by"
              " the Shortest Path routing algorithm, using the greatest possible "
              " bitrate and any modulation scheme. If it's possible to establish "
              " such connection, then the network is said to be \"transparent\"."
              << std::endl;
}

void Simulation_TransparencyAnalysis::run()
{
    if (!hasLoaded)
        {
        load();
        }

    if (hasRun)
        {
        return;
        }

    for (double avgSpan = minAvgLinkSpan; avgSpan <= maxAvgLinkSpan;
            avgSpan += stepAvgLinkSpan)
        {
        for (double inOSNR = minOSNR; inOSNR <= maxOSNR; inOSNR += stepOSNR)
            {
            Signal::InputOSNR = Gain(inOSNR, Gain::dB);

            std::shared_ptr<Topology> TopCopy(new Topology(*T));
            TopCopy->set_avgSpanLength(avgSpan);
            std::weak_ptr<Node> origin, destination;

            for (auto node : TopCopy->Nodes)
                {
                if (node->ID == Orig_Origin->ID)
                    {
                    origin = node;
                    }

                if (node->ID == Orig_Destination->ID)
                    {
                    destination = node;
                    }
                }

            std::shared_ptr<ShortestPath> SP(new ShortestPath(TopCopy));
            std::shared_ptr<FirstFit> FF(new FirstFit(TopCopy));

            RoutingWavelengthAssignment RWA(SP, FF, ModulationScheme::DefaultSchemes,
                                            TopCopy);
            std::shared_ptr<Call> C(new Call(origin, destination, *maxBitrate));

            if (RWA.routeCall(C) != nullptr)
                {
                TransparentPoints.push_back(InLineDistance_OSNR_Point(avgSpan, inOSNR));
                }
            else
                {
                OpaquePoints.push_back(InLineDistance_OSNR_Point(avgSpan, inOSNR));
                }
            }
        }

    hasRun = true;
}

void Simulation_TransparencyAnalysis::load()
{
    //Generic readings.
    SimulationType::load();

    std::cout << std::endl <<
              "-> Define the minimum average distance between in-line amplifiers" <<
              std::endl;

    do
        {
        std::cin >> minAvgLinkSpan;

        if (std::cin.fail() || minAvgLinkSpan < 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid distance." << std::endl;
            std::cout << std::endl <<
                      "-> Define the minimum average distance between in-line amplifiers" <<
                      std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl <<
              "-> Define the maximum average distance between in-line amplifiers"
              << std::endl;

    do
        {
        std::cin >> maxAvgLinkSpan;

        if (std::cin.fail() || maxAvgLinkSpan < minAvgLinkSpan)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid distance." << std::endl;
            std::cout << std::endl <<
                      "-> Define the maximum average distance between in-line amplifiers"
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl <<
              "-> Define the average distance between in-line amplifiers step."
              << std::endl;

    do
        {
        std::cin >> stepAvgLinkSpan;

        if (std::cin.fail() || stepAvgLinkSpan < 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid distance." << std::endl;
            std::cout << std::endl <<
                      "-> Define the average distance between in-line amplifiers step."
                      << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the minimum input OSNR" << std::endl;

    do
        {
        std::cin >> minOSNR;

        if (std::cin.fail())
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid OSNR." << std::endl;
            std::cout << "-> Define the minimum input OSNR" << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the maximum input OSNR" << std::endl;

    do
        {
        std::cin >> maxOSNR;

        if (std::cin.fail() || maxOSNR < minOSNR)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid OSNR." << std::endl;
            std::cout << "-> Define the maximum input OSNR" << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    std::cout << std::endl << "-> Define the input OSNR step." << std::endl;

    do
        {
        std::cin >> stepOSNR;

        if (std::cin.fail() || stepOSNR < 0)
            {
            std::cin.clear();
            std::cin.ignore();

            std::cerr << "Invalid OSNR." << std::endl;
            std::cout << "-> Define the input OSNR step." << std::endl;
            }
        else
            {
            break;
            }
        }
    while (1);

    find_OriginDestination();

    hasLoaded = true;
}

void Simulation_TransparencyAnalysis::load_file(std::string)
{

}

void Simulation_TransparencyAnalysis::save(std::string)
{

}

void Simulation_TransparencyAnalysis::print()
{
    if (!hasLoaded)
        {
        load();
        }

    if (!hasRun)
        {
        run();
        }

    std::cout << std::endl << "* * RESULTS * *" << std::endl;

    if (!TransparentPoints.empty())
        {
        std::cout << std::endl << "Transparent Points: " << std::endl;

        for (auto &pair : TransparentPoints)
            {
            std::cout << "[" << pair.first << "km, " << pair.second << "dB] ";
            }
        }

    if (!OpaquePoints.empty())
        {
        std::cout << std::endl << "Opaque Points: " << std::endl;

        for (auto &pair : OpaquePoints)
            {
            std::cout << "[" << pair.first << "km, " << pair.second << "dB] ";
            }
        }
}

void Simulation_TransparencyAnalysis::find_OriginDestination()
{
    ShortestPath SP(T);
    double maxLength = -1;

    for (auto orig : T->Nodes)
        {
        for (auto dest : T->Nodes)
            {
            if (orig == dest)
                {
                continue;
                }

            std::shared_ptr<Call> DummyCall(new Call(orig, dest, 0));
            auto links = SP.route(DummyCall);
            double length = 0;

            for (auto link : links)
                {
                length += link.lock()->Length;
                }

            if (maxLength < length)
                {
                maxLength = length;
                Orig_Origin = orig;
                Orig_Destination = dest;
                }
            }
        }
}
