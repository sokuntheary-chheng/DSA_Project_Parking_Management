#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include "vehicle.h"
#include "linkedlist.h"
#include "sorting.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "bst.h"
#include "fileio.h"
using namespace std;

#define TOTAL_SLOTS 300
#define CAR_SLOT_FROM 1
#define CAR_SLOT_TO 50
#define MOTO_SLOT_FROM 51
#define MOTO_SLOT_TO 300

bool slotOccupied[TOTAL_SLOTS + 1];

int findFreeSlot(int from, int to) {
    for (int i = from; i <= to; i++) {
        if (!slotOccupied[i]) return i;
    }
    return -1;
}

string toLowerStr(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

int readIntChoice() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
    return value;
}

bool isValidTime(string t) {
    if (t.length() != 5) return false;
    if (t[2] != ':') return false;
    for (int i = 0; i < (int)t.length(); i++) {
        if (i == 2) continue;
        if (!isdigit(t[i])) return false;
    }
    int hour = stoi(t.substr(0, 2));
    int minute = stoi(t.substr(3, 2));
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;
    return true;
}

int main() {
    for (int i = 0; i <= TOTAL_SLOTS; i++) slotOccupied[i] = false;

    List* parkingList = createEmptyList();
    Stack* actionStack = createEmptyStack();
    Queue* waitingQueue = createEmptyQueue();
    HashTable* ht = createHashTable();
    BSTNode* bstRoot = nullptr;

    loadFromCSV(parkingList, ht, &bstRoot);

    Element* tmp = parkingList->head;
    while (tmp != nullptr) {
        slotOccupied[tmp->data.slotID] = true;
        tmp = tmp->next;
    }

    int choice;
    do {
        cout << "\n====== UNIVERSITY PARKING SYSTEM ======" << endl;
        cout << " Slots 1-50: Cars | Slots 51-300: Motorcycles" << endl;
        cout << "========================================" << endl;
        cout << "1.  Park a vehicle" << endl;
        cout << "2.  Remove a vehicle" << endl;
        cout << "3.  View waiting queue" << endl;
        cout << "4.  Add vehicle to waiting queue" << endl;
        cout << "5.  Undo last action" << endl;
        cout << "6.  Search vehicle by plate (Hash Table)" << endl;
        cout << "7.  Display all parked vehicles (Linked List)" << endl;
        cout << "8.  Sort vehicles" << endl;
        cout << "9.  Browse slots by ID (BST in-order)" << endl;
        cout << "10. Update vehicle entry time" << endl;
        cout << "11. View recent action history" << endl;
        cout << "12. Peek next vehicle in waiting queue" << endl;
        cout << "13. View BST pre-order / post-order" << endl;
        cout << "14. Display hash table contents" << endl;
        cout << "15. Count total parked vehicles (BST)" << endl;
        cout << "16. Save and Exit" << endl;
        cout << "Enter choice: ";
        choice = readIntChoice();
        cout << endl;

        // 1. Park a vehicle
        if (choice == 1) {
            string plate, time, type;
            cout << "Vehicle type (car / motorcycle): ";
            cin >> type;
            type = toLowerStr(type);

            if (type != "car" && type != "motorcycle") {
                cout << "Invalid vehicle type. Please enter 'car' or 'motorcycle'." << endl;
                continue;
            }

            cout << "Plate number: ";
            cin >> plate;
            if (plate.empty()) {
                cout << "Plate cannot be empty." << endl;
                continue;
            }

            Vehicle existing;
            if (searchHT(ht, plate, existing)) {
                cout << "Vehicle " << plate << " is already parked at slot " << existing.slotID << endl;
                continue;
            }

            cout << "Entry time (HH:MM): ";
            cin >> time;
            if (!isValidTime(time)) {
                cout << "Invalid time format. Please use HH:MM (e.g. 09:30)." << endl;
                continue;
            }

            int slotFrom, slotTo;
            if (type == "car") {
                slotFrom = CAR_SLOT_FROM; slotTo = CAR_SLOT_TO;
            } else {
                slotFrom = MOTO_SLOT_FROM; slotTo = MOTO_SLOT_TO;
            }

            int slot = findFreeSlot(slotFrom, slotTo);
            if (slot == -1) {
                cout << "No free slot for " << type << ". Adding to waiting queue." << endl;
                Vehicle v;
                v.plate = plate;
                v.type = type;
                v.slotID = -1;
                v.entryTime = time;
                enqueue(waitingQueue, v);
            } else {
                Vehicle v;
                v.plate = plate;
                v.type = type;
                v.slotID = slot;
                v.entryTime = time;

                addEnd(parkingList, v);
                insertHT(ht, v);
                bstRoot = insertBST(bstRoot, v);
                slotOccupied[slot] = true;

                ActionRecord record;
                record.actionType = "PARK";
                record.v = v;
                push(actionStack, record);

                cout << "Vehicle " << plate << " parked at slot " << slot << endl;
            }
        }

        // 2. Remove a vehicle
        else if (choice == 2) {
            string plate;
            cout << "Enter plate to remove: ";
            cin >> plate;
            if (plate.empty()) {
                cout << "Plate cannot be empty." << endl;
                continue;
            }

            Vehicle found;
            if (searchHT(ht, plate, found)) {
                deleteByPlate(parkingList, plate);
                deleteHT(ht, plate);
                bstRoot = deleteBST(bstRoot, found.slotID);
                slotOccupied[found.slotID] = false;

                ActionRecord record;
                record.actionType = "REMOVE";
                record.v = found;
                push(actionStack, record);

                cout << "Vehicle " << plate << " removed from slot " << found.slotID << endl;

                if (!isEmptyQueue(waitingQueue)) {
                    Vehicle next = dequeue(waitingQueue);
                    bool freedIsCarSlot = (found.slotID >= CAR_SLOT_FROM && found.slotID <= CAR_SLOT_TO);

                    if ((freedIsCarSlot && next.type == "car") ||
                        (!freedIsCarSlot && next.type == "motorcycle")) {
                        next.slotID = found.slotID;
                        addEnd(parkingList, next);
                        insertHT(ht, next);
                        bstRoot = insertBST(bstRoot, next);
                        slotOccupied[found.slotID] = true;
                        cout << "Vehicle " << next.plate << " moved from queue to slot " << found.slotID << endl;
                    } else {
                        enqueue(waitingQueue, next);
                        cout << "Freed slot type doesn't match next vehicle in queue; queue order kept." << endl;
                    }
                }
            } else {
                cout << "Vehicle " << plate << " not found." << endl;
            }
        }

        // 3. View waiting queue
        else if (choice == 3) {
            displayQueue(waitingQueue);
        }

        // 4. Add to waiting queue manually
        else if (choice == 4) {
            string plate, time, type;
            cout << "Vehicle type (car / motorcycle): ";
            cin >> type;
            type = toLowerStr(type);
            if (type != "car" && type != "motorcycle") {
                cout << "Invalid vehicle type." << endl;
                continue;
            }

            cout << "Plate number: ";
            cin >> plate;
            if (plate.empty()) {
                cout << "Plate cannot be empty." << endl;
                continue;
            }

            Vehicle existing;
            if (searchHT(ht, plate, existing)) {
                cout << "Vehicle " << plate << " is already parked at slot " << existing.slotID << endl;
                continue;
            }

            cout << "Entry time (HH:MM): ";
            cin >> time;

            Vehicle v;
            v.plate = plate;
            v.type = type;
            v.slotID = -1;
            v.entryTime = time;
            enqueue(waitingQueue, v);
        }

        // 5. Undo last action
        else if (choice == 5) {
            if (isEmptyStack(actionStack)) {
                cout << "Nothing to undo." << endl;
            } else {
                ActionRecord last = pop(actionStack);
                if (last.actionType == "PARK") {
                    deleteByPlate(parkingList, last.v.plate);
                    deleteHT(ht, last.v.plate);
                    bstRoot = deleteBST(bstRoot, last.v.slotID);
                    slotOccupied[last.v.slotID] = false;
                    cout << "Undo PARK: Vehicle " << last.v.plate
                         << " removed from slot " << last.v.slotID << endl;
                } else if (last.actionType == "REMOVE") {
                    addEnd(parkingList, last.v);
                    insertHT(ht, last.v);
                    bstRoot = insertBST(bstRoot, last.v);
                    slotOccupied[last.v.slotID] = true;
                    cout << "Undo REMOVE: Vehicle " << last.v.plate
                         << " restored to slot " << last.v.slotID << endl;
                }
            }
        }

        // 6. Search by plate
        else if (choice == 6) {
            string plate;
            cout << "Enter plate to search: ";
            cin >> plate;
            if (plate.empty()) {
                cout << "Plate cannot be empty." << endl;
                continue;
            }
            Vehicle result;
            if (searchHT(ht, plate, result)) {
                cout << "Found -> Plate: " << result.plate
                     << " | Type: " << result.type
                     << " | Slot: " << result.slotID
                     << " | Entry Time: " << result.entryTime << endl;
            } else {
                cout << "Vehicle " << plate << " not found." << endl;
            }
        }

        // 7. Display all parked vehicles
        else if (choice == 7) {
            displayAll(parkingList);
        }

        // 8. Sort vehicles
        else if (choice == 8) {
            cout << "Sort by:" << endl;
            cout << "1. Plate number" << endl;
            cout << "2. Slot ID" << endl;
            cout << "3. Entry time" << endl;
            cout << "Choice: ";
            int sortChoice = readIntChoice();
            if (sortChoice == 1) {
                sortByPlate(parkingList);
            } else if (sortChoice == 2) {
                sortBySlot(parkingList);
            } else if (sortChoice == 3) {
                sortByTime(parkingList);
            } else {
                cout << "Invalid choice." << endl;
                continue;
            }
            displayAll(parkingList);
        }

        // 9. Browse slots by ID (BST in-order)
        else if (choice == 9) {
            cout << "All occupied slots in ascending order:" << endl;
            inOrder(bstRoot);
        }

        // 10. Update vehicle entry time
        else if (choice == 10) {
            string plate, newTime;
            cout << "Enter plate to update: ";
            cin >> plate;
            Vehicle found;
            if (!searchHT(ht, plate, found)) {
                cout << "Vehicle " << plate << " not found." << endl;
                continue;
            }
            cout << "Enter new entry time (HH:MM): ";
            cin >> newTime;
            updateByPlate(parkingList, plate, newTime);
            updateHT(ht, plate, newTime);
            cout << "Entry time updated for " << plate << endl;
        }

        // 11. View recent action history (Stack)
        else if (choice == 11) {
            displayStack(actionStack);
        }

        // 12. Peek next vehicle in waiting queue
        else if (choice == 12) {
            if (isEmptyQueue(waitingQueue)) {
                cout << "Waiting queue is empty." << endl;
            } else {
                Vehicle next = getFront(waitingQueue);
                cout << "Next in queue -> Plate: " << next.plate
                     << " | Type: " << next.type
                     << " | Waiting since: " << next.entryTime << endl;
            }
        }

        // 13. BST pre-order / post-order view
        else if (choice == 13) {
            cout << "Pre-order traversal:" << endl;
            preOrder(bstRoot);
            cout << "\nPost-order traversal:" << endl;
            postOrder(bstRoot);
        }

        // 14. Display hash table contents
        else if (choice == 14) {
            displayHT(ht);
        }

        // 15. Count total parked vehicles (BST)
        else if (choice == 15) {
            cout << "Total parked vehicles (via BST count): " << countBST(bstRoot) << endl;
        }

        // 16. Save and Exit
        else if (choice == 16) {
            saveToCSV(parkingList);
            clearStack(actionStack);
            clearQueue(waitingQueue);
            cout << "Goodbye!" << endl;
        }

        else {
            cout << "Invalid choice. Please enter 1-16." << endl;
        }

    } while (choice != 16);

    return 0;
}