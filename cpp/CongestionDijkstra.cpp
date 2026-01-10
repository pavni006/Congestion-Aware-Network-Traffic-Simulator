#include "CongestionDijkstra.h"

#include <queue>
#include <limits>
#include <algorithm>

std::vector<int> CongestionDijkstra::shortestPath(
    const Graph &graph,
    int source,
    int destination)
{
    int n = graph.getNumNodes();

    std::vector<double> distance(
        n,
        std::numeric_limits<double>::max());

    std::vector<int> parent(
        n,
        -1);

    using Pair = std::pair<double, int>;

    std::priority_queue<
        Pair,
        std::vector<Pair>,
        std::greater<Pair>>
        pq;

    distance[source] = 0;

    pq.push({0, source});

    const double ALPHA = 100.0;

    while (!pq.empty())
    {
        Pair current = pq.top();

        double currentDistance = current.first;
        int node = current.second;

        pq.pop();

        if (currentDistance > distance[node])
        {
            continue;
        }

        if (node == destination)
        {
            break;
        }

        for (const auto &edge : graph.getNeighbors(node))
        {

            if (!edge.active)
            {
                continue;
            }
            double utilization =
                edge.currentLoad / edge.capacity;

            double edgeCost =
                edge.latency;

            double newDistance =
                distance[node] +
                edgeCost;

            if (newDistance < distance[edge.to])
            {
                distance[edge.to] = newDistance;

                parent[edge.to] = node;

                pq.push(
                    {newDistance,
                     edge.to});
            }
        }
    }

    std::vector<int> path;

    int current = destination;

    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    std::reverse(
        path.begin(),
        path.end());

    return path;
}

std::vector<int> CongestionDijkstra::leastCongestedPath(
    const Graph &graph,
    int source,
    int destination)
{
    int n = graph.getNumNodes();

    std::vector<double> distance(
        n,
        std::numeric_limits<double>::max());

    std::vector<int> parent(
        n,
        -1);

    using Pair = std::pair<double, int>;

    std::priority_queue<
        Pair,
        std::vector<Pair>,
        std::greater<Pair>>
        pq;

    distance[source] = 0;

    pq.push({0, source});

    const double ALPHA = 100.0;

    while (!pq.empty())
    {
        Pair current = pq.top();

        double currentDistance = current.first;
        int node = current.second;

        pq.pop();

        if (currentDistance > distance[node])
        {
            continue;
        }

        if (node == destination)
        {
            break;
        }

        for (const auto &edge : graph.getNeighbors(node))
        {

            if (!edge.active)
            {
                continue;
            }
            double utilization =
                edge.currentLoad / edge.capacity;

            double edgeCost =
                edge.latency +
                (ALPHA * utilization);

            double newDistance =
                distance[node] +
                edgeCost;

            if (newDistance < distance[edge.to])
            {
                distance[edge.to] = newDistance;

                parent[edge.to] = node;

                pq.push(
                    {newDistance,
                     edge.to});
            }
        }
    }

    std::vector<int> path;

    if (distance[destination] ==
        std::numeric_limits<double>::max())
    {
        return path;
    }

    int current = destination;

    while (current != -1)
    {
        path.push_back(current);
        current = parent[current];
    }

    std::reverse(
        path.begin(),
        path.end());

    return path;
}