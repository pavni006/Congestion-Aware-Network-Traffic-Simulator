#pragma once

#include "Graph.h"

#include <vector>

class Dijkstra
{
public:
    static std::vector<int> shortestPath(
        const Graph& graph,
        int source,
        int destination
    );
};