#include "Graph.h"

#include <iostream>

double Graph::getLatency(
    int from,
    int to
) const
{
    for(const auto& edge : adjList[from])
    {
        if(edge.to == to)
        {
            return edge.latency;
        }
    }

    return -1;
}

Graph::Graph(int nodes)
{
    adjList.resize(nodes);
}

void Graph::addEdge(
    int from,
    int to,
    double capacity,
    double latency
)
{
    Edge edge;

    edge.to = to;
    edge.capacity = capacity;
    edge.currentLoad = 0;
    edge.latency = latency;
    edge.active = true;

    adjList[from].push_back(edge);

    Edge reverseEdge;

    reverseEdge.to = from;
    reverseEdge.capacity = capacity;
    reverseEdge.currentLoad = 0;
    reverseEdge.latency = latency;
    reverseEdge.active = true;

    adjList[to].push_back(reverseEdge);
}

void Graph::printGraph() const
{
    for(int i = 0; i < adjList.size(); i++)
    {
        std::cout << "Router "
                  << i
                  << " -> ";

        for(const auto& edge : adjList[i])
        {
            std::cout
                << "("
                << edge.to
                << ", cap="
                << edge.capacity
                << ", lat="
                << edge.latency
                << ") ";
        }

        std::cout << std::endl;
    }
}

const std::vector<Edge>& Graph::getNeighbors(int node) const
{
    return adjList[node];
}

int Graph::getNumNodes() const
{
    return adjList.size();
}

double Graph::getUtilization(
    int from,
    int to
) const
{
    for(const auto& edge : adjList[from])
    {
        if(edge.to == to)
        {
            return edge.currentLoad
                   / edge.capacity;
        }
    }

    return 0;
}

void Graph::disableEdge(
    int from,
    int to
)
{
    for(auto& edge : adjList[from])
    {
        if(edge.to == to)
        {
            edge.active = false;
        }
    }

    for(auto& edge : adjList[to])
    {
        if(edge.to == from)
        {
            edge.active = false;
        }
    }
}

bool Graph::isEdgeActive(
    int from,
    int to
) const
{
    for(const auto& edge : adjList[from])
    {
        if(edge.to == to)
        {
            return edge.active;
        }
    }

    return false;
}

void Graph::setCurrentLoad(
    int from,
    int to,
    double load
)
{
    for(auto& edge : adjList[from])
    {
        if(edge.to == to)
        {
            edge.currentLoad = load;
        }
    }

    for(auto& edge : adjList[to])
    {
        if(edge.to == from)
        {
            edge.currentLoad = load;
        }
    }
}

void Graph::addLoad(
    int from,
    int to,
    double load
)
{
    for(auto& edge : adjList[from])
    {
        if(edge.to == to)
        {
            edge.currentLoad += load;
        }
    }

    for(auto& edge : adjList[to])
    {
        if(edge.to == from)
        {
            edge.currentLoad += load;
        }
    }
}

void Graph::printUtilization() const
{
    for(int i = 0; i < adjList.size(); i++)
    {
        for(const auto& edge : adjList[i])
        {
            if(i < edge.to)
            {
                std::cout
                    << i
                    << "-"
                    << edge.to
                    << " : "
                    << edge.currentLoad
                    << "/"
                    << edge.capacity
                    << std::endl;
            }
        }
    }
}

void Graph::removeLoad(
    int from,
    int to,
    double load
)
{
    for(auto& edge : adjList[from])
    {
        if(edge.to == to)
        {
            edge.currentLoad -= load;

            if(edge.currentLoad < 0)
            {
                edge.currentLoad = 0;
            }
        }
    }

    for(auto& edge : adjList[to])
    {
        if(edge.to == from)
        {
            edge.currentLoad -= load;

            if(edge.currentLoad < 0)
            {
                edge.currentLoad = 0;
            }
        }
    }
}

bool Graph::canAddLoad(
    int from,
    int to,
    double load
) const
{
    for(const auto& edge : adjList[from])
    {
        if(edge.to == to)
        {
            return (
                edge.currentLoad + load
                <= edge.capacity
            );
        }
    }

    return false;
}

double Graph::getCongestionCost(
    int from,
    int to
) const
{
    for(const auto& edge : adjList[from])
    {
        if(edge.to == to)
        {
            double utilization =
                edge.currentLoad /
                edge.capacity;

            return edge.latency *
                   (1 + utilization);
        }
    }

    return 1e9;
}