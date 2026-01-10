#include "Graph.h"
#include "Simulator.h"

#include <iostream>

#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(nullptr));

    Graph network(8);

    network.addEdge(0, 1, 100, 10);
    network.addEdge(0, 2, 100, 15);

    network.addEdge(1, 3, 20, 10);
    network.addEdge(2, 3, 120, 10);

    network.addEdge(1, 4, 100, 20);
    network.addEdge(2, 5, 100, 20);

    network.addEdge(4, 6, 100, 10);
    network.addEdge(5, 6, 100, 10);

    network.addEdge(6, 7, 150, 10);

    network.addEdge(3, 7, 80, 15);

    Simulator sim(network);

    for (int i = 0; i < 50; i++)
    {
        int source =
            rand() % 8;

        int destination =
            rand() % 8;

        while (destination == source)
        {
            destination =
                rand() % 8;
        }

        sim.schedulePacket(
            source,
            destination,
            20,
            rand() % 20);
    }

    while (!sim.isFinished())
    {
        if (sim.getCurrentTime() % 5 == 0)
        {
            sim.printStatus();
        }
        sim.advanceTick();
    }

    sim.printStatus();

    sim.exportCSV(
        "../results/simulation.csv");

    SimulationStats stats =
        sim.getStats();

    std::cout
        << "\nPackets Created: "
        << stats.packetsCreated
        << std::endl;

    std::cout
        << "Packets Delivered: "
        << stats.packetsDelivered
        << std::endl;

    std::cout
        << "Packets Waiting: "
        << stats.packetsWaiting
        << std::endl;

    std::cout
        << "Packets Dropped: "
        << stats.packetsDropped
        << std::endl;

    std::cout
        << "Average Latency: "
        << stats.averageLatency
        << std::endl;

    return 0;
}