#include "Dijkstra.h"

#include <queue>
#include <limits>
#include <algorithm>

std::vector<int> Dijkstra::shortestPath(
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

    while (!pq.empty())
    {
        Pair current = pq.top();

        double currentDistance = current.first;
        int node = current.second;

        pq.pop();

        if (node == destination)
        {
            break;
        }

        for (const auto &edge :
             graph.getNeighbors(node))
        {
            double newDistance =
                distance[node] + edge.latency;

            if (newDistance <
                distance[edge.to])
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