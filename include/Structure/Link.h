#ifndef LINK_H
#define LINK_H

#include <GeneralClasses/Signal.h>
#include <memory>
#include <vector>
#include <string>
#include <fstream>

class Node;
class Call;
class Slot;
class Topology;
namespace Devices
{
class Device;
}

/**
 * @brief The Link class represents a link.
 */
class Link
{
public:
    /**
     * @brief NumSlots is the number of frequency slots on this link.
     */
    static int NumSlots;
    /**
     * @brief DefaultAvgSpanLength is the average distance between successive
     * in line amplifiers, in kilometers.
     */
    static double DefaultAvgSpanLength;

    /**
     * @brief AvgSpanLength is the distance between successive in line amplifiers,
     * on this link. It is aproximately equal to DefaultAvgSpanLength.
     */
    double AvgSpanLength;

    /**
     * @brief Link is the standard constructor to a Link object.
     * @param Origin is a pointer to the origin node.
     * @param Destination is a pointer to the destination node.
     * @param Length is the length of this link, in kilometers.
     */
    Link(std::weak_ptr<Node> Origin, std::weak_ptr<Node> Destination,
         double Length);
    /**
     * @brief Link is the copy constructor of a Link object.
     * @param link is the Link being copied.
     */
    Link(const Link &link);

    /**
     * @brief Origin is a pointer to the origin node.
     */
    std::weak_ptr<Node> Origin;
    /**
     * @brief Destination is a pointer to the destination node.
     */
    std::weak_ptr<Node> Destination;
    /**
     * @brief Slots is a vector containing the frequency slots of this link.
     */
    std::vector<std::shared_ptr<Slot>> Slots;
    /**
     * @brief Devices is a vector containing the optical Devices of this link.
     */
    std::vector<std::shared_ptr<Devices::Device>> Devices;

    /**
     * @brief Length is the length of this link, in kilometers.
     */
    double Length;
    /**
     * @brief numLineAmplifiers is the number of in line amplifiers.
     */
    int numLineAmplifiers;

    bool operator==(const Link &) const;
    bool operator<(const Link &) const;

    /**
     * @brief isSlotFree returns true iff the i-th slot is free.
     * @return true iff the i-th slot is free.
     */
    bool isSlotFree(int) const;

    /**
     * @brief bypass bypasses a signal by all the optical devices of this link.
     * Observe that the parameter Signal is modified through the bypassing.
     * @return the Signal after it bypassed all the optical devices of this link.
     */
    Signal &bypass(Signal &);

    /**
     * @brief get_Availability returns the availability of this link, i.e. the
     * number of free slots.
     * @return the availability of this link.
     */
    int get_Availability();
    /**
     * @brief get_Occupability returns the occupability of this link, i.e. the
     * number of occupied slots.
     * @return the occupability of this link.
     */
    int get_Occupability();
    /**
     * @brief get_Contiguity returns the contiguity measure of this link. This
     * measure is how many ways it is possible to allocate the required slots by
     * Call C on this link.
     * @param C is the Call against whom the contiguity measured is calculated.
     * @return in how many ways it is possible to allocate the required slots by
     * Call C on this link.
     */
    int get_Contiguity(std::shared_ptr<Call> C);

    /**
     * @brief get_CapEx returns the CapEx of this link.
     * @return the CapEx of this link.
     */
    double get_CapEx();
    /**
     * @brief get_OpEx returns the OpEx of this link.
     * @return the OpEx of this link.
     */
    double get_OpEx();

    /**
     * @brief load reads parameters required to construct the links on the Topology T.
     * @param T is the topology being constructed.
     */
    static void load(std::shared_ptr<Topology> T);
    /**
     * @brief save saves the parameters that were required to construct the links
     * on the Topology T.
     * @param T is the topology constructed.
     */
    static void save(std::string, std::shared_ptr<Topology> T);
    /**
     * @brief set_AvgSpanLength is used to set the average length between in line
     * amplifiers.
     * @param avgSpanLength is the new average length between in line amplifiers.
     */
    void set_AvgSpanLength(double avgSpanLength);

    /**
     * @brief is_LinkActive returns true iff this link is active, i.e., new connections can
     * pass through it. If it's inactive, no new traffic can pass through this link.
     * @return true iff this link is active.
     */
    bool is_LinkActive() const
    {
        return isActive;
    }
    /**
     * @brief set_LinkActive sets the link as active.
     */
    void set_LinkActive();
    /**
     * @brief set_LinkInactive sets the link as inactive.
     */
    void set_LinkInactive();

    friend std::ostream& operator<<(std::ostream &out, const Link &link);

private:
    void create_Slots();
    void create_Devices();

    bool isActive;
};

#endif // LINK_H
