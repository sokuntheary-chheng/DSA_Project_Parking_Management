#include <iostream>
#include <fstream>
#include <string>
#include "fileio.h"
using namespace std;

void saveToCSV(List* ls) {
    ofstream file("parking_data.csv");
    file << "plate,type,slotID,entryTime" << endl;
    Element* e = ls->head;
    while (e != nullptr) {
        file << e->data.plate << ","
             << e->data.type << ","
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

        int c1 = line.find(',');
        int c2 = line.find(',', c1 + 1);
        int c3 = line.find(',', c2 + 1);

        if (c1 == (int)string::npos || c2 == (int)string::npos || c3 == (int)string::npos) {
            cout << "Skipping corrupted line in CSV." << endl;
            continue;
        }

        try {
            Vehicle v;
            v.plate = line.substr(0, c1);
            v.type = line.substr(c1 + 1, c2 - c1 - 1);
            v.slotID = stoi(line.substr(c2 + 1, c3 - c2 - 1));
            v.entryTime = line.substr(c3 + 1);
            addEnd(ls, v);
            insertHT(ht, v);
            *bstRoot = insertBST(*bstRoot, v);
            count++;
        } catch (...) {
            cout << "Skipping invalid data line in CSV." << endl;
            continue;
        }
    }
    file.close();
    cout << count << " vehicle(s) loaded from parking_data.csv" << endl;
}