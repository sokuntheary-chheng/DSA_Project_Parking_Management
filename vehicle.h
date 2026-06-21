// vehicle.h
#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
using namespace std;

struct Vehicle {
    string plate;       // "ABC-1234"
    string type;        // "Car" or "Motorcycle"
    int slotID;         // 1-250 car, 251-300 motorcycle, -1 if waiting in queue
    string entryTime;   // "14:35"
};

#endif