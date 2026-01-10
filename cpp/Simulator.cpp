#include "Simulator.h"
#include "CongestionDijkstra.h"

#include <iostream>

#include <fstream>


void Simulator::exportCSV(
    const std::string &filename)
{
    std::ofstream file(filename);

    file
        << "time,"
        << "created,"
        << "delivered,"
        << "waiting,"
        << "dropped,"
        << "avg_latency,"
        << "throughput,"
        << "packet_loss\n";

    for (const auto &tick : history)
    {
        file
            << tick.time << ","
            << tick.created << ","
            << tick.delivered << ","
            << tick.waiting << ","
            << tick.dropped << ","
            << tick.averageLatency << ","
            << tick.throughput << ","
            << tick.packetLoss
            << "\n";
    }

    file.close();
}

Simulator::Simulator(
    const Graph &graph)
    : network(graph)
{
    currentTime = 0;
}

void Simulator::addPacket(
    int source,
    int destination,
    double size)
{
    Packet packet;

    packet.id =
        packets.size();

    packet.source =
        source;

    packet.destination =
        destination;

    packet.route =
        CongestionDijkstra::shortestPath(
            network,
            source,
            destination);

    packet.currentPosition = 0;

    packet.remainingTravelTime = 0;

    packet.delivered = false;

    packet.size = size;

    packet.waitTicks = 0;
    packet.dropped = false;

    packet.previousFrom = -1;
    packet.previousTo = -1;

    packet.waiting = false;

    packet.waitTicks = 0;

    packet.dropped = false;

    packet.creationTime =
        currentTime;

    packet.deliveryTime =
        -1;

    stats.packetsCreated++;

    // std::cout
    //     << "Packet "
    //     << packet.id
    //     << " Route: ";

    // for (int node : packet.route)
    // {
    //     std::cout << node << " ";
    // }

    // std::cout << std::endl;

    packets.push_back(packet);
}

void Simulator::advanceTick()
{

    for (const auto &request : pendingPackets)
    {
        if (request.arrivalTime == currentTime)
        {
            addPacket(
                request.source,
                request.destination,
                request.size);
        }
    }
    currentTime++;

    if (currentTime == 30)
    {
        std::cout
            << "\n*** LINK FAILURE: 1-3 ***\n";

        network.disableEdge(
            1,
            3);
    }

    stats.packetsWaiting = 0;

    for (auto &packet : packets)
    {
        if (packet.delivered || packet.dropped)
        {
            continue;
        }

        if (packet.remainingTravelTime > 0)
        {
            packet.remainingTravelTime--;

            if (packet.remainingTravelTime == 0)
            {
                network.removeLoad(
                    packet.previousFrom,
                    packet.previousTo,
                    packet.size);

                packet.currentPosition++;

                packet.previousFrom = -1;
                packet.previousTo = -1;
            }

            continue;
        }

        if (packet.currentPosition >=
            packet.route.size() - 1)
        {
            if (packet.previousFrom != -1)
            {
                network.removeLoad(
                    packet.previousFrom,
                    packet.previousTo,
                    packet.size);

                packet.previousFrom = -1;
                packet.previousTo = -1;
            }

            packet.delivered = true;

            packet.deliveryTime =
                currentTime;
            stats.packetsDelivered++;
            continue;
        }

        int from =
            packet.route[packet.currentPosition];

        int to =
            packet.route[packet.currentPosition + 1];

        if (packet.previousFrom != -1)
        {
            network.removeLoad(
                packet.previousFrom,
                packet.previousTo,
                packet.size);

            packet.previousFrom = -1;
            packet.previousTo = -1;
        }

        if (
            network.isEdgeActive(
                from,
                to) &&
            network.canAddLoad(
                from,
                to,
                packet.size))
        {
            packet.waiting = false;
            packet.waitTicks = 0;

            network.addLoad(
                from,
                to,
                packet.size);

            packet.previousFrom = from;
            packet.previousTo = to;

            packet.remainingTravelTime =
                network.getLatency(
                    from,
                    to);
        }
        else
        {
            if (!packet.waiting)
            {
                packet.route =
                    CongestionDijkstra::
                        leastCongestedPath(
                            network,
                            packet.route[packet.currentPosition],
                            packet.destination);

                if (packet.route.empty())
                {
                    packet.dropped = true;
                    stats.packetsDropped++;
                    continue;
                }

                packet.currentPosition = 0;
            }
            packet.waiting = true;

            packet.waitTicks++;

            stats.packetsWaiting++;

            if (packet.waitTicks > 10)
            {
                packet.dropped = true;

                stats.packetsDropped++;
            }
        }
    }

    TickStats tick;

    tick.time = currentTime;

    tick.created =
        stats.packetsCreated;

    tick.delivered =
        stats.packetsDelivered;

    tick.waiting =
        stats.packetsWaiting;

    tick.dropped =
        stats.packetsDropped;

    tick.averageLatency =
        getStats().averageLatency;

    tick.throughput =
        getStats().throughput;

    tick.packetLoss =
        getStats().packetLossRate;

    history.push_back(tick);
}

void Simulator::schedulePacket(
    int source,
    int destination,
    double size,
    int arrivalTime)
{
    PacketRequest request;

    request.source = source;
    request.destination = destination;
    request.size = size;
    request.arrivalTime = arrivalTime;

    pendingPackets.push_back(request);
}

SimulationStats
Simulator::getStats() const
{
    SimulationStats result =
        stats;

    double totalLatency = 0;

    int deliveredCount = 0;

    result.throughput =
        (double)stats.packetsDelivered /
        currentTime;

    result.packetLossRate =
        100.0 *
        stats.packetsDropped /
        stats.packetsCreated;

    for (const auto &packet : packets)
    {
        if (packet.delivered)
        {
            totalLatency +=
                packet.deliveryTime -
                packet.creationTime;

            deliveredCount++;
        }
    }

    if (deliveredCount > 0)
    {
        result.averageLatency =
            totalLatency /
            deliveredCount;
    }

    return result;
}

bool Simulator::isFinished() const
{
    for (const auto &packet : packets)
    {
        if (!packet.delivered &&
            !packet.dropped)
        {
            return false;
        }
    }

    for (const auto &request : pendingPackets)
    {
        if (request.arrivalTime >= currentTime)
        {
            return false;
        }
    }

    return true;
}

void Simulator::printStatus() const
{
    std::cout
        << "\nTime: "
        << currentTime
        << "\n";

    for (const auto &packet : packets)
    {

        if (packet.delivered)
        {
            continue;
        }
        std::cout
            << "Packet "
            << packet.id
            << " ";

        if (packet.delivered)
        {
            std::cout
                << "Delivered";
        }
        else if (packet.dropped)
        {
            std::cout
                << "Dropped";
        }
        else
        {
            if (packet.remainingTravelTime > 0)
            {
                std::cout
                    << "Travelling "
                    << packet.previousFrom
                    << " -> "
                    << packet.previousTo
                    << " ("
                    << packet.remainingTravelTime
                    << " ticks left)";
            }
            else
            {
                std::cout
                    << "At Router "
                    << packet.route[packet.currentPosition];

                if (packet.waiting)
                {
                    std::cout
                        << " (WAITING)";
                }
            }
        }

        std::cout
            << std::endl;

        // network.printUtilization();
    }
    network.printUtilization();
}

int Simulator::getCurrentTime() const
{
    return currentTime;
}