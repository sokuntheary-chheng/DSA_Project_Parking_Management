#include <iostream>
#include "hashtable.h"
using namespace std;

int hashFunction(string plate) {
    int sum = 0;
    for (int i = 0; i < (int)plate.length(); i++) {
        sum += plate[i];
    }
    return sum % TABLE_SIZE;
}

HashTable* createHashTable() {
    HashTable* ht = new HashTable;
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->buckets[i] = nullptr;
    }
    return ht;
}

void insertHT(HashTable* ht, Vehicle v) {
    int index = hashFunction(v.plate);
    HNode* newNode = new HNode;
    newNode->data = v;
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
}

bool searchHT(HashTable* ht, string plate, Vehicle& result) {
    int index = hashFunction(plate);
    HNode* current = ht->buckets[index];
    while (current != nullptr) {
        if (current->data.plate == plate) {
            result = current->data;
            return true;
        }
        current = current->next;
    }
    return false;
}

void deleteHT(HashTable* ht, string plate) {
    int index = hashFunction(plate);
    HNode* current = ht->buckets[index];
    HNode* prev = nullptr;
    while (current != nullptr) {
        if (current->data.plate == plate) {
            if (prev == nullptr)
                ht->buckets[index] = current->next;
            else
                prev->next = current->next;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Vehicle " << plate << " not found in hash table." << endl;
}

void displayHT(HashTable* ht) {
    cout << "--- Hash Table Contents ---" << endl;
    bool empty = true;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->buckets[i] != nullptr) {
            empty = false;
            cout << "[" << i << "]: ";
            HNode* current = ht->buckets[i];
            while (current != nullptr) {
                cout << current->data.plate << " (Slot " << current->data.slotID << ")";
                if (current->next != nullptr) cout << " -> ";
                current = current->next;
            }
            cout << endl;
        }
    }
    if (empty) cout << "Hash table is empty." << endl;
}

void updateHT(HashTable* ht, string plate, string newTime) {
    int index = hashFunction(plate);
    HNode* current = ht->buckets[index];
    while (current != nullptr) {
        if (current->data.plate == plate) {
            current->data.entryTime = newTime;
            return;
        }
        current = current->next;
    }
    cout << "Vehicle " << plate << " not found." << endl;
}