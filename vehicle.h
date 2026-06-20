#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

struct Vehicle {
    std::string plate;
    std::string type;
    int slotID;
    std::string entryTime;
};

#endif