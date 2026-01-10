cmake_minimum_required(VERSION 3.10)

project(
    DynamicNetworkSimulator
)

set(
    CMAKE_CXX_STANDARD
    17
)

add_executable(
    simulator

    cpp/main.cpp

    cpp/Graph.cpp
    cpp/Simulator.cpp

    cpp/Dijkstra.cpp
    cpp/CongestionDijkstra.cpp
)