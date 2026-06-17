#include <iostream>
#include "queue.h"
using namespace std;

Queue* createEmptyQueue() {
    Queue* q = new Queue;
    q->n = 0;
    q->front = nullptr;
    q->rear = nullptr;
    return q;
}

void enqueue(Queue* q, Vehicle v) {
    QElement* e = new QElement;
    e->data = v;
    e->next = nullptr;
    if (q->n == 0) {
        q->front = e;
        q->rear = e;
    } else {
        q->rear->next = e;
        q->rear = e;
    }
    q->n++;
    cout << "Vehicle " << v.plate << " added to waiting queue." << endl;
}

Vehicle dequeue(Queue* q) {
    if (q->n == 0) {
        cout << "Queue is empty." << endl;
        Vehicle empty;
        empty.plate = "";
        return empty;
    }
    QElement* tmp = q->front;
    Vehicle v = tmp->data;
    q->front = tmp->next;
    if (q->front == nullptr) q->rear = nullptr;
    delete tmp;
    q->n--;
    return v;
}

bool isEmptyQueue(Queue* q) {
    return q->n == 0;
}

void displayQueue(Queue* q) {
    if (q->n == 0) {
        cout << "Waiting queue is empty." << endl;
        return;
    }
    cout << "--- Waiting Queue (" << q->n << " vehicle(s)) ---" << endl;
    QElement* current = q->front;
    int pos = 1;
    while (current != nullptr) {
        cout << pos++ << ". Plate: " << current->data.plate
            << " | Entry Time: " << current->data.entryTime << endl;
        current = current->next;
    }
}