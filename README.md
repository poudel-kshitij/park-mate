# Park-Mate: Smart Parking Management System

### A C++ simulation of a multi-zone parking management system featuring:
- **Heap-based priority parking** for VIP and emergency vehicles  
- **Graph-based shortest path search** using **Dijkstra’s Algorithm**  
- **Interactive command-line interface** to manage parking, retrieval, and real-time status

---

## Project Overview

**Park-Mate** is an advanced parking management system built entirely in **C++**, designed to demonstrate real-world data-structure applications.  
It integrates:
- **Queues** for general parking and exit flow  
- **Heaps (Priority Queues)** to allocate *priority parking* efficiently  
- **Graphs and Dijkstra’s Algorithm** to compute the *shortest route* between any entry and exit point in the lot  

This project combines **algorithmic logic** and **system simulation** — a perfect blend of *data structures, graph theory, and real-world systems modeling*.

---

## System Architecture

| Component | Description |
|------------|-------------|
| `Vehicle.h` | Defines the vehicle class (ID, type, timestamp, and priority attributes). |
| `ParkingZone.h` | Models each parking zone, managing queues, slot assignments, and exits. |
| `ParkingSystem.h` | Central controller that coordinates parking logic and integrates graph traversal. |
| `Graph.h` | Implements adjacency list representation and Dijkstra’s shortest path algorithm. |
| `main.cpp` | User interface: menu-driven program for simulation and testing. |

---

## Key Features

**Priority Parking:**  
Implements a **min-heap** structure to ensure VIP or emergency vehicles always get the closest available slots.

**Shortest Path Finder:**  
Uses **Dijkstra’s algorithm** on a manually defined adjacency list to compute the optimal route to entry/exit zones.

**Zone Management:**  
Supports multiple parking zones with unique slot identifiers (`LxQyIz`) for clear organization.

**Interactive Simulation:**  
Menu-based interface to:
- Enter car  
- Exit car
- Show parking status  
- Find shortest path to your car
- Exit menu

---

## Installation & Compilation

## Clone this repository
bash
git clone https://github.com/poudel-kshitij/park-mate.git
cd park-mate

## Compile this project
g++ -std=c++17 main.cpp -o parkmate
(If you later add .cpp implementations for headers, include them too:)

g++ -std=c++17 main.cpp Graph.cpp ParkingSystem.cpp ParkingZone.cpp -o parkmate

## Run the program
./parkmate       # (Mac/Linux)
parkmate.exe     # (Windows)
