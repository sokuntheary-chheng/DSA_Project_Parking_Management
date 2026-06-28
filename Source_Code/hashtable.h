#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "vehicle.h"

#define TABLE_SIZE 307

struct HNode {
    Vehicle data;
    HNode* next;
};

struct HashTable {
    HNode* buckets[TABLE_SIZE];
};

int hashFunction(string plate);
HashTable* createHashTable();
void insertHT(HashTable* ht, Vehicle v);
bool searchHT(HashTable* ht, string plate, Vehicle& result);
void deleteHT(HashTable* ht, string plate);
void displayHT(HashTable* ht);
void updateHT(HashTable* ht, string plate, string newTime);

#endif