#pragma once

#include <vector>

struct Edge
{
    int to;
    double capacity;
    double currentLoad;
    double latency;
    bool active;
};

class Graph
{
private:
    std::vector<std::vector<Edge>> adjList;

public:
    Graph(int nodes);

    void addEdge(
        int from,
        int to,
        double capacity,
        double latency);

    void printGraph() const;

    const std::vector<Edge> &getNeighbors(int node) const;

    double getUtilization(
        int from,
        int to) const;

    void setCurrentLoad(
        int from,
        int to,
        double load);

    void addLoad(
        int from,
        int to,
        double load);

    void printUtilization() const;

    void removeLoad(
        int from,
        int to,
        double load);

    int getNumNodes() const;

    bool canAddLoad(
        int from,
        int to,
        double load) const;

    double getLatency(
        int from,
        int to) const;

    double getCongestionCost(
        int from,
        int to) const;

    void disableEdge(
        int from,
        int to);

    bool isEdgeActive(
        int from,
        int to) const;
};