// vehicle.h
#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
using namespace std;

struct Vehicle {
    string plate;      // e.g. "ABC-1234"
    int slotID;        // e.g. 5
    string entryTime;  // e.g. "08:30"
};

#endif