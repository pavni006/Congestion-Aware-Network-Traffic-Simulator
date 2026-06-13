# Congestion-Aware Network Traffic Simulator

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Python](https://img.shields.io/badge/Python-3.10+-yellow)
![Build](https://img.shields.io/badge/Build-CMake-green)

A packet-level network simulator built in C++ that models network traffic flow, congestion, routing decisions, link failures, packet drops, and network performance metrics.

---

## 📌 Overview

Modern networks must dynamically route data while managing varying traffic bursts, queue overhead, and link failures. This project models these behaviors by representing network infrastructures as directed graphs. The core C++ engine tracks packet state changes over a discrete time loop, applying adaptive algorithms to minimize bottlenecks.

The framework is decoupled into two explicit processing layers:
1. **Simulation Engine (C++):** Manages topology memory, graph mutations, routing algorithms, and performance logging.
2. **Analytics UI (Python):** Ingests execution logs to process, evaluate, and render network health metrics.

---

## 🛠️ Features

* **🌐 Core Network Engine:** Builds graph-based network topologies mapping bidirectional routers (nodes) and communication links (edges) with distinct capacity and latency weights.
* **🎯 Adaptive Routing Solver:** Implements a modified Dijkstra algorithm utilizing dynamic cost metrics to compute alternate paths around saturated lines.
* **💥 Fault-Tolerance Simulation:** Models runtime edge failures, triggers automatic route recomputation, and handles packet drops gracefully.
* **📈 Queue & Traffic Controls:** Features admission control systems using resource-tracking queues to block, buffer, or discard packets during high-load intervals.
* **📊 Analytics Suite:** Exports historical metrics directly to structured CSVs, leveraging a Pandas and Matplotlib dashboard to plot throughput trends and latency heatmaps.

---

## 📐 System Architecture

The simulation isolates high-performance backend calculations from analytics reporting via a structured data pipeline:

```text
+-----------------------+     +------------------------+     +------------------------+
| 📦 1. TRAFFIC ENGINE  |     | 🧠 2. ROUTING ENGINE   |     | 🕸️ 3. CORE SIMULATOR   |
| Generates Packets     | --> | Computes Paths         | --> | Mutates Adjacency List |
| Schedules Arrival     |     | Cost = Latency + Load  |     | Handles Edge Failures  |
+-----------------------+     +------------------------+     +------------------------+
                                                                         |
                                                                         v
+-----------------------+     +------------------------+     +------------------------+
| 📊 6. UI DASHBOARD    |     | 📄 5. LOGGING LAYER    |     | 📈 4. STATISTICS ENGINE|
| Renders Matplotlib Plots| <-- | Exports Results        | <-- | Aggregates Latency     |
| Pandas Data Analytics |     | results/simulation.csv |     | Calculates Throughput  |
+-----------------------+     +------------------------+     +------------------------+
```

---

## Routing Strategy

The simulator uses a modified Dijkstra algorithm.

Instead of considering only latency, routing decisions incorporate current network congestion:

```

Cost = Latency + α × Utilization

```

Where:

- Latency = Link transmission delay
- Utilization = CurrentLoad / Capacity
- α = Congestion penalty coefficient

This encourages packets to avoid heavily congested paths even if they are shorter.

---

## Link Failure Simulation

The simulator supports dynamic link failures during execution.

Example:

```cpp
network.disableEdge(1, 3);
```

When a link becomes unavailable:

1. Packets attempting to use the failed link are blocked.
2. The routing algorithm recalculates an alternative path.
3. Traffic is redirected if a valid route exists.
4. Packets are dropped if no path is available.

---

## Performance Metrics

The simulator tracks:

| Metric | Description |
|----------|------------|
| Packets Created | Total generated packets |
| Packets Delivered | Successfully delivered packets |
| Packets Dropped | Packets discarded due to failures or excessive waiting |
| Packets Waiting | Packets currently blocked by congestion |
| Average Latency | Average delivery time of successful packets |
| Throughput | Delivered packets per simulation tick |
| Packet Loss Rate | Percentage of dropped packets |

---

## Project Structure

```text
Congestion-Aware-Network-Traffic-Simulator
│
├── cpp/
│   ├── Graph.cpp / .h             # Adjacency list and graph definitions
│   ├── Simulator.cpp / .h         # Discrete event scheduling loop
│   ├── CongestionDijkstra.cpp/.h  # Adaptive routing algorithm logic
│   └── main.cpp                   # Simulation runner and data exporter
│
├── python/
│   └── dashboard.py               # Data analytics and visualization framework
│
├── results/
│   └── sample_output.csv          # Generated simulation performance logs
│
├── CMakeLists.txt                 # C++ project build specification
├── requirements.txt               # Python visualization environment tools
└── README.md
```

---

## Building the Project

### Prerequisites

- C++17 compatible compiler
- CMake 3.15+
- Python 3.10+

### Build

```bash
cmake -B build
cmake --build build
```

---

## Running the Simulation

Execute:

```bash
./build/simulator
```

The simulator will:

- Generate packets
- Route traffic
- Simulate congestion
- Handle failures
- Export simulation statistics

Output CSV:

```text
results/simulation.csv
```

---

## Python Dashboard

Install dependencies:

```bash
pip install -r requirements.txt
```

Run:

```bash
python python/dashboard.py
```

The dashboard visualizes:

- Packet delivery trends
- Average latency over time
- Waiting packets
- Network performance metrics

---

## Dashboard Preview

The simulator exports performance metrics to CSV files which can be visualized using the Python analytics dashboard.

The dashboard provides:

- Packet creation, delivery, waiting and drop statistics
- Average packet latency over time
- Throughput monitoring
- Packet loss analysis

### Example Output

![Dashboard Preview](assets/dashboard.png)

---

## Experimental Results

A sample simulation with 50 packets demonstrates:

- Successful packet delivery under congestion
- Dynamic rerouting after link failures
- Congestion-aware path selection
- Packet dropping under prolonged network saturation

Observed metrics:

| Metric | Value |
|----------|----------|
| Packets Created | 50 |
| Packets Delivered | 41 |
| Packets Dropped | 9 |
| Peak Waiting Packets | 10 |
| Final Throughput | ~0.57 packets/tick |
| Packet Loss Rate | 18% |
| Average Latency | ~30 ticks |
---

## Technologies Used

### Backend

- C++
- STL
- Object-Oriented Design

### Algorithms

- Dijkstra's Algorithm
- Priority Queue Based Routing
- Congestion-Aware Cost Modeling

### Data Processing

- CSV Export

### Visualization

- Python
- Pandas
- Matplotlib

---
