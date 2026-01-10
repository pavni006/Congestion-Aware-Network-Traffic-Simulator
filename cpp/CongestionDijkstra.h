#pragma once

#include "Graph.h"

#include <vector>

class CongestionDijkstra
{
public:
    static std::vector<int> shortestPath(
        const Graph &graph,
        int source,
        int destination);

    static std::vector<int> leastCongestedPath(
        const Graph &graph,
        int source,
        int destination);
};