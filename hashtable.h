#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include "vehicle.h"

#define TABLE_SIZE 307

struct HNode {
    Vehicle data;
    HNode* next;
};

struct HashTable {
    HNode* buckets[TABLE_SIZE];
    int n;
};

int hashFunction(std::string plate);
HashTable* createHashTable();
void insertHT(HashTable* ht, Vehicle v);
bool searchHT(HashTable* ht, std::string plate, Vehicle& result);
void deleteHT(HashTable* ht, std::string plate);
void updateHT(HashTable* ht, std::string plate, std::string newTime);
void displayHT(HashTable* ht);
int getHTSize(HashTable* ht);

#endif