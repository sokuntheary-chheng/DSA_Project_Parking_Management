// linkedlist.cpp
#include "linkedlist.h"
#include <iostream>
using namespace std;

List* createEmptyList() {
    List* ls = new List;
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

// function to add a vehicle to the end of the list
void addEnd(List* ls, Vehicle v) {
    Element* e = new Element;
    e->data = v;
    e->next = nullptr;
    if (ls->n == 0) {
        ls->head = e;
    } else {
        ls->tail->next = e;
    }
    ls->tail = e;
    ls->n++;
}

// function to delete a vehicle by its plate number
void deleteByPlate(List* ls, string plate) {
    Element* current = ls->head;
    Element* previous = nullptr;
    while (current != nullptr) {
        if (current->data.plate == plate) {
            if (previous == nullptr) { // Deleting head
                ls->head = current->next;
            } else {
                previous->next = current->next;
            }
            if (current == ls->tail) { // Deleting tail
                ls->tail = previous;
            }
            delete current;
            ls->n--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

bool searchByPlate(List* ls, string plate, Vehicle& result) {
    Element* current = ls->head;
    while (current != nullptr) {
        if (current->data.plate == plate) {
            result = current->data;
            return true;
        }
        current = current->next;
    }
    return false;
}

void updateByPlate(List* ls, string plate, string newTime) {
    Element* current = ls->head;
    while (current != nullptr) {
        if (current->data.plate == plate) {
            current->data.entryTime = newTime;
            return;
        }
        current = current->next;
    }
}

// function to display all vehicles in the list
void displayAll(List* ls) {
    if (ls->n == 0) {
        cout << "No vehicles parked." << endl;
        return;
    }
    Element* current = ls->head;
    while (current != nullptr) {
        cout << "Plate: " << current->data.plate
             << " | Slot: " << current->data.slotID
             << " | Time: " << current->data.entryTime << endl;
        current = current->next;
    }
}