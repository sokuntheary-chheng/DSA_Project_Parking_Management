#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "vehicle.h"
#include <string>
using namespace std;

struct Element {
    Vehicle data;
    Element* next;
};

struct List {
    int n;
    Element* head;
    Element* tail;
};

List* createEmptyList();
void addEnd(List* ls, Vehicle v);
void deleteByPlate(List* ls, string plate);
bool searchByPlate(List* ls, string plate, Vehicle& result);
void updateByPlate(List* ls, string plate, string newTime);
void displayAll(List* ls);

#endif