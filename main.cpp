#include "ParkingSystem.h"
#include <iostream>

int main() {
    ParkingSystem parkingSystem;
    parkingSystem.initializeParkingLot();

    std::cout << "--- Welcome to ParkMate ---\n";
    while (true) {
        std::cout << "Choose an option:\n";
        std::cout << "1. Enter car\n";
        std::cout << "2. Exit car\n";
        std::cout << "3. Show parking status\n";
        std::cout << "4. Find shortest path to your car\n";
        std::cout << "5. Exit\n";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string vehicleNumber;
            std::cout << "Enter vehicle number: ";
            std::cin >> vehicleNumber;
            parkingSystem.enterCar(vehicleNumber);
        } else if (choice == 2) {
            std::string vehicleNumber;
            std::cout << "Enter vehicle number: ";
            std::cin >> vehicleNumber;
            parkingSystem.exitCar(vehicleNumber);
        } else if (choice == 3) {
            parkingSystem.showStatus();
        } else if (choice == 4) {
            std::string entrance;
            std::cout << "Enter your current entrance (E1, E2, E3): ";
            std::cin >> entrance;

            std::string vehicleOrSlot;
            std::cout << "Enter your vehicle number or destination slot ID: ";
            std::cin >> vehicleOrSlot;

            parkingSystem.findShortestPath(entrance, vehicleOrSlot);
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}