#pragma once

#include "Graph.h"

#include <vector>

#include <string>

struct Packet
{
    int id;

    int source;
    int destination;

    double size;

    int currentPosition;

    int previousFrom;
    int previousTo;

    int creationTime;
    int deliveryTime;

    int remainingTravelTime;

    std::vector<int> route;

    bool waiting;
    bool delivered;

    int waitTicks;
    bool dropped;
};

struct PacketRequest
{
    int source;
    int destination;
    double size;
    int arrivalTime;
};

struct SimulationStats
{
    int packetsCreated = 0;

    int packetsDelivered = 0;

    int packetsWaiting = 0;

    int packetsDropped = 0;

    double averageLatency = 0;

    double throughput;
    double packetLossRate;
};

struct TickStats
{
    int time;

    int created;

    int delivered;

    int waiting;

    int dropped;

    double averageLatency;

    double throughput;

    double packetLoss;
};

class Simulator
{
private:
    Graph network;

    std::vector<Packet> packets;

    std::vector<PacketRequest> pendingPackets;

    int currentTime;

    SimulationStats stats;

    // remove this
    std::vector<TickStats> history;

public:
    Simulator(const Graph &graph);

    SimulationStats getStats() const;

    // remove this
    void exportCSV(
        const std::string &filename);

    void addPacket(
        int source,
        int destination,
        double size);

    void advanceTick();

    int getCurrentTime() const;

    void printStatus() const;

    void schedulePacket(
        int source,
        int destination,
        double size,
        int arrivalTime);

    bool isFinished() const;
};