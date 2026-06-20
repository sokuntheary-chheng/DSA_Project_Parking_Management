#include <iostream>
#include <fstream>
#include <string>
#include "fileio.h"
using namespace std;

void saveToCSV(List* ls) {
    ofstream file("parking_data.csv");
    file << "plate,slotID,entryTime" << endl;
    Element* e = ls->head;
    while (e != nullptr) {
        file << e->data.plate << ","
             << e->data.slotID << ","
             << e->data.entryTime << endl;
        e = e->next;
    }
    file.close();
    cout << "Data saved to parking_data.csv" << endl;
}

void loadFromCSV(List* ls, HashTable* ht, BSTNode** bstRoot) {
    ifstream file("parking_data.csv");
    if (!file.is_open()) {
        cout << "No existing data file found. Starting fresh." << endl;
        return;
    }
    string line;
    getline(file, line); // skip header row
    int count = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;
        Vehicle v;
        int c1 = line.find(',');
        int c2 = line.find(',', c1 + 1);
        v.plate = line.substr(0, c1);
        v.slotID = stoi(line.substr(c1 + 1, c2 - c1 - 1));
        v.entryTime = line.substr(c2 + 1);
        addEnd(ls, v);
        insertHT(ht, v);
        *bstRoot = insertBST(*bstRoot, v);
        count++;
    }
    file.close();
    cout << count << " vehicle(s) loaded from parking_data.csv" << endl;
}