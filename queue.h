#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
#include "vehicle.h"

using namespace std;

struct QElement {
    Vehicle data;
    QElement* next;
};

struct Queue {
    int n;
    QElement* front;
    QElement* rear;
};

Queue* createEmptyQueue();
void enqueue(Queue* q, Vehicle v);
Vehicle dequeue(Queue* q);
bool isEmptyQueue(Queue* q);
void displayQueue(Queue* q);

#endif