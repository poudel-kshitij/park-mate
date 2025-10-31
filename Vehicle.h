#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

struct Vehicle {
    std::string vehicleNumber;
    int entryTime;

    Vehicle(const std::string& number, int time) : vehicleNumber(number), entryTime(time) {}
};

#endif // VEHICLE_H