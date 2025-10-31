#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H

#include "ParkingZone.h"
#include "Graph.h"
#include "Vehicle.h"
#include <unordered_map>
#include <iostream>
#include <chrono>
#include <string>
#include <stdexcept>
#include <iomanip> // For formatting prices

class ParkingSystem {
public:
    ParkingSystem();
    void initializeParkingLot();
    void enterCar(const std::string& vehicleNumber);
    void exitCar(const std::string& vehicleNumber);
    void showStatus();
    void findShortestPath(const std::string& entrance, const std::string& vehicleOrSlot);

private:
    Graph graph;
    std::unordered_map<int, ParkingZone> slots;
    std::unordered_map<std::string, int> vehicleToSlot;
    std::unordered_map<std::string, int> entranceToNode;
    std::unordered_map<int, double> zonePricing; // Zone pricing
    int totalSlots;

    void prefillParkingLot(); // Pre-fill parking lot with vehicles
    int getCurrentTime();
    double calculatePrice(int zoneId, int entryTime);
};

ParkingSystem::ParkingSystem() : totalSlots(0) {}

void ParkingSystem::initializeParkingLot() {
    int slotId = 1;

    // Zone 3 (High Priority): 27 slots
    for (int i = 0; i < 27; ++i) {
        slots[slotId] = ParkingZone(slotId, 3);
        graph.addNode(slotId);
        if (i > 0) graph.addEdge(slotId - 1, slotId, 2); // Distance: 2 meters
        slotId++;
    }

    // Zone 2 (Medium Priority): 54 slots
    for (int i = 0; i < 54; ++i) {
        slots[slotId] = ParkingZone(slotId, 2);
        graph.addNode(slotId);
        if (i > 0) graph.addEdge(slotId - 1, slotId, 3); // Distance: 3 meters
        slotId++;
    }

    // Zone 1 (Low Priority): 81 slots
    for (int i = 0; i < 81; ++i) {
        slots[slotId] = ParkingZone(slotId, 1);
        graph.addNode(slotId);
        if (i > 0) graph.addEdge(slotId - 1, slotId, 4); // Distance: 4 meters
        slotId++;
    }

    // Add entrances as nodes
    int entranceE1 = slotId++;
    int entranceE2 = slotId++;
    int entranceE3 = slotId++;

    entranceToNode["E1"] = entranceE1;
    entranceToNode["E2"] = entranceE2;
    entranceToNode["E3"] = entranceE3;

    graph.addNode(entranceE1);
    graph.addNode(entranceE2);
    graph.addNode(entranceE3);

    // Connect entrances to the first slot in each zone
    graph.addEdge(entranceE1, 1, 5);   // E1 to Zone 1
    graph.addEdge(entranceE2, 82, 5);  // E2 to Zone 2
    graph.addEdge(entranceE3, 136, 5); // E3 to Zone 3

    // Set zone pricing
    zonePricing[1] = 2.0; // Zone 1: $2/hour
    zonePricing[2] = 3.0; // Zone 2: $3/hour
    zonePricing[3] = 5.0; // Zone 3: $5/hour

    totalSlots = slotId - 1;
    std::cout << "Parking lot initialized with " << totalSlots << " slots and entrances.\n";

    // Pre-fill the parking lot with vehicles
    prefillParkingLot();
}



void ParkingSystem::prefillParkingLot() {
    for (int i = 1; i <= 100; ++i) {
        std::string vehicleNumber = "KA-01-HH-" + std::to_string(1000 + i);
        for (auto& [slotId, slot] : slots) {
            if (slot.vehicleNumber.empty()) {
                slot.vehicleNumber = vehicleNumber;
                vehicleToSlot[vehicleNumber] = slotId;
                break;
            }
        }
    }
    std::cout << "Pre-filled parking lot with 50 vehicles.\n";
}

void ParkingSystem::enterCar(const std::string& vehicleNumber) {
    int parkingOption;
    std::cout << "Choose a parking option:\n";
    std::cout << "1. Priority Parking (Automatically park in the highest-priority available zone)\n";
    std::cout << "2. Manual Zone Selection\n";
    std::cin >> parkingOption;

    
    if (parkingOption == 1) {
        // Priority Parking
        for (int priorityZone = 3; priorityZone >= 1; --priorityZone) {
            for (auto& [slotId, slot] : slots) {
                if (slot.zoneId == priorityZone && slot.vehicleNumber.empty()) {
                    slot.vehicleNumber = vehicleNumber;
                    vehicleToSlot[vehicleNumber] = slotId;
                    std::cout << "Vehicle " << vehicleNumber << " parked at slot " << slotId << " in Zone " << priorityZone << ".\n";
                    return;
                }
            }
        }
        std::cout << "No available slots in any zone.\n";
    } else if (parkingOption == 2) {
        // Manual Zone Selection
        int preferredZone;
        std::cout << "Choose a zone to park your vehicle:\n";
        std::cout << "1. Zone 3 (High Priority, $5/hour)\n";
        std::cout << "2. Zone 2 (Medium Priority, $3/hour)\n";
        std::cout << "3. Zone 1 (Low Priority, $2/hour)\n";
        std::cin >> preferredZone;

        if (preferredZone < 1 || preferredZone > 3) {
            std::cout << "Invalid zone selection. Please try again.\n";
            return;
        }

        for (auto& [slotId, slot] : slots) {
            if (slot.zoneId == preferredZone && slot.vehicleNumber.empty()) {
                slot.vehicleNumber = vehicleNumber;
                vehicleToSlot[vehicleNumber] = slotId;
                std::cout << "Vehicle " << vehicleNumber << " parked at slot " << slotId << " in Zone " << preferredZone << ".\n";
                return;
            }
        }

        std::cout << "No available slots in Zone " << preferredZone << ".\n";
    } else {
        std::cout << "Invalid parking option. Please try again.\n";
    }
}

void ParkingSystem::exitCar(const std::string& vehicleNumber) {
    if (vehicleToSlot.find(vehicleNumber) != vehicleToSlot.end()) {
        int slotId = vehicleToSlot[vehicleNumber];
        int zoneId = slots[slotId].zoneId;
        int entryTime = getCurrentTime(); // Simulate entry time for now
        double price = calculatePrice(zoneId, entryTime);

        slots[slotId].vehicleNumber.clear();
        vehicleToSlot.erase(vehicleNumber);

        std::cout << "Vehicle " << vehicleNumber << " exited from slot " << slotId << ".\n";
        std::cout << "Total price: $" << std::fixed << std::setprecision(2) << price << "\n";
    } else {
        std::cout << "Vehicle " << vehicleNumber << " not found.\n";
    }
}

void ParkingSystem::showStatus() {
    for (const auto& [slotId, slot] : slots) {
        std::cout << "Slot " << slotId << " (Zone " << slot.zoneId << "): ";
        if (slot.vehicleNumber.empty()) {
            std::cout << "Empty\n";
        } else {
            std::cout << "Occupied by " << slot.vehicleNumber << "\n";
        }
    }
}

void ParkingSystem::findShortestPath(const std::string& entrance, const std::string& vehicleOrSlot) {
    int sourceNode;
    int destinationNode;

    // Determine the source node from the entrance
    if (entranceToNode.find(entrance) != entranceToNode.end()) {
        sourceNode = entranceToNode[entrance];
    } else {
        std::cout << "Invalid entrance. Please enter E1, E2, or E3.\n";
        return;
    }

    // Determine the destination node
    if (vehicleToSlot.find(vehicleOrSlot) != vehicleToSlot.end()) {
        destinationNode = vehicleToSlot[vehicleOrSlot]; // Vehicle number provided
    } else {
        try {
            destinationNode = std::stoi(vehicleOrSlot); // Slot ID provided
            if (slots.find(destinationNode) == slots.end()) {
                std::cout << "Invalid slot ID.\n";
                return;
            }
        } catch (std::invalid_argument&) {
            std::cout << "Invalid input. Please enter a valid vehicle number or slot ID.\n";
            return;
        }
    }

    // Find the shortest path using Dijkstra's algorithm
    std::vector<int> path = graph.shortestPath(sourceNode, destinationNode);
    std::cout << "Shortest path from " << entrance << " to destination: ";
    for (int node : path) {
        std::cout << node << " ";
    }
    std::cout << "\n";
}

int ParkingSystem::getCurrentTime() {
    return std::chrono::duration_cast<std::chrono::seconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
}

double ParkingSystem::calculatePrice(int zoneId, int entryTime) {
    int currentTime = getCurrentTime();
    int duration = (currentTime - entryTime) / 3600; // Convert seconds to hours
    if (duration == 0) duration = 1; // Minimum charge for 1 hour
    return duration * zonePricing[zoneId];
}

#endif // PARKINGSYSTEM_H