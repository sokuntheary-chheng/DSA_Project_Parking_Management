#include <iostream>
#include "linkedlist.h"
using namespace std;

List* createEmptyList() {
    List* ls = new List;
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

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

void deleteByPlate(List* ls, string plate) {
    if (ls->n == 0) {
        cout << "List is empty." << endl;
        return;
    }
    Element* current = ls->head;
    Element* prev = nullptr;

    while (current != nullptr) {
        if (current->data.plate == plate) {
            if (prev == nullptr) {
                // delete at head
                ls->head = current->next;
            } else {
                prev->next = current->next;
            }
            if (current->next == nullptr) {
                // deleted tail
                ls->tail = prev;
            }
            delete current;
            ls->n--;
            cout << "Vehicle " << plate << " removed from list." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Vehicle " << plate << " not found in list." << endl;
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
            cout << "Entry time updated for " << plate << endl;
            return;
        }
        current = current->next;
    }
    cout << "Vehicle " << plate << " not found." << endl;
}

void displayAll(List* ls) {
    if (ls->n == 0) {
        cout << "No vehicles parked." << endl;
        return;
    }
    Element* current = ls->head;
    cout << "\n--- Parked Vehicles (" << ls->n << ") ---" << endl;
    while (current != nullptr) {
        cout << "Plate: " << current->data.plate
            << " | Slot: " << current->data.slotID
            << " | Time: " << current->data.entryTime << endl;
        current = current->next;
    }
}