#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <map>
#include <memory>
#include <RMSA/TransparentSegment.h>

namespace RMSA
{
/**
 * @brief The Route class is the result of RMSA Algorithms. Contains a set of
 * transparent segments, over which a Call can be implemented. Each Transparent
 * segment might be ended with a Translucent Node.
 */
class Route
{
public:
    /**
     * @brief Route is the standard constructor for a Route.
     * @param Segments is a vector of TransparentSegment used to implement the
     * call.
     *
     * If the simulation is transparent, then this vector contains a single one
     * TransparentSegment.
     * @param Slots is a map of the set of slots used in each link traversed
     * by the route.
     */
    Route(std::vector<TransparentSegment> Segments,
          std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
          std::owner_less<std::weak_ptr<Link>>> Slots);
    /**
     * @brief Route is the copy constructor for a Route.
     * @param route is a pointer to another Route.
     */
    Route(const Route &route);

    /**
     * @brief Regenerators is a map with the number of regenerators used in each
     * node.
     */
    std::map<std::weak_ptr<Node>, unsigned int,
        std::owner_less<std::weak_ptr<Node>>> Regenerators;

    /**
     * @brief Segments is a vector of TransparentSegment used to implement the
     * call.
     */
    std::vector<TransparentSegment> Segments;
    /**
     * @brief Nodes is a vector of nodes traversed through the Route.
     */
    std::vector<std::weak_ptr<Node>> Nodes;
    /**
     * @brief Links is a vector of links traversed through the Route.
     */
    std::vector<std::weak_ptr<Link>> Links;
    /**
     * @brief Slots is a map of the set of slots used in each link traversed
     * by the route.
     */
    std::map<std::weak_ptr<Link>, std::vector<std::weak_ptr<Slot>>,
        std::owner_less<std::weak_ptr<Link>>> Slots;

    /**
     * @brief bypass is used to analyze the signal quality after it has traversed
     * the Route.
     * @param S is the input signal.
     * @return the Signal after it has traversed the route.
     */
    Signal bypass(Signal S);
    /**
     * @brief partial_bypass is used to analyze the signal quality after it has
     * traversed part of the Route.
     * @param S is the input signal.
     * @param orig is a pointer to the first considered Node in the Route.
     * @param dest is a pointer to the last considered Node in the Route.
     * @return the Signal after it has traversed part of the route.
     */
    Signal &partial_bypass(Signal &S,
                           std::weak_ptr<Node> orig,
                           std::weak_ptr<Node> dest);
};
}

#endif // ROUTE_H
