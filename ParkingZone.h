#ifndef PARKINGZONE_H
#define PARKINGZONE_H

#include <string>

struct ParkingZone {
    int slotId;
    int zoneId;
    std::string vehicleNumber;
    ParkingZone() : slotId(0), zoneId(0), vehicleNumber("") {}

    ParkingZone(int id, int zone) : slotId(id), zoneId(zone), vehicleNumber("") {}
};

#endif // PARKINGZONE_H