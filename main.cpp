#include <iostream>
#include <string>
#include "vehicle.h"
#include "linkedlist.h"
#include "sorting.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "bst.h"
#include "fileio.h"
using namespace std;

#define TOTAL_SLOTS 200

// Track which slots are occupied: false = free, true = occupied
bool slotOccupied[TOTAL_SLOTS + 1]; // index 1..200

// Find first free slot in range [from, to]
int findFreeSlot(int from, int to) {
    for (int i = from; i <= to; i++) {
        if (!slotOccupied[i]) return i;
    }
    return -1; // no free slot
}

int main() {
    // Initialize slot tracker
    for (int i = 0; i <= TOTAL_SLOTS; i++) slotOccupied[i] = false;

    // Create all data structures
    List* parkingList = createEmptyList();
    Stack* actionStack = createEmptyStack();
    Queue* waitingQueue = createEmptyQueue();
    HashTable* ht = createHashTable();
    BSTNode* bstRoot = nullptr;

    // Load saved data
    loadFromCSV(parkingList, ht, &bstRoot);

    // Mark loaded slots as occupied
    Element* tmp = parkingList->head;
    while (tmp != nullptr) {
        slotOccupied[tmp->data.slotID] = true;
        tmp = tmp->next;
    }

    int choice;
    do {
        cout << "\n====== UNIVERSITY PARKING SYSTEM ======" << endl;
        cout << " Slots 1-150: Motorcycles | Slots 151-200: Cars" << endl;
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
        cout << "10. Save and Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;

        // 1. Park a vehicle
        if (choice == 1) {
            string plate, time, type;
            cout << "Vehicle type (car / motorcycle): ";
            cin >> type;
            cout << "Plate number: ";
            cin >> plate;
            cout << "Entry time (HH:MM): ";
            cin >> time;

            int slotFrom, slotTo;
            if (type == "car") {
                slotFrom = 151; slotTo = 200;
            } else {
                slotFrom = 1; slotTo = 150;
            }

            int slot = findFreeSlot(slotFrom, slotTo);
            if (slot == -1) {
                cout << "No free slot for " << type << ". Adding to waiting queue." << endl;
                Vehicle v;
                v.plate = plate;
                v.slotID = -1;
                v.entryTime = time;
                enqueue(waitingQueue, v);
            } else {
                Vehicle v;
                v.plate = plate;
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

                // Check waiting queue — assign freed slot
                if (!isEmptyQueue(waitingQueue)) {
                    cout << "Assigning freed slot to next vehicle in queue..." << endl;
                    Vehicle next = dequeue(waitingQueue);
                    int slotFrom = (found.slotID <= 150) ? 1 : 151;
                    int slotTo   = (found.slotID <= 150) ? 150 : 200;
                    int newSlot  = findFreeSlot(slotFrom, slotTo);
                    if (newSlot != -1) {
                        next.slotID = newSlot;
                        addEnd(parkingList, next);
                        insertHT(ht, next);
                        bstRoot = insertBST(bstRoot, next);
                        slotOccupied[newSlot] = true;
                        cout << "Vehicle " << next.plate << " moved from queue to slot " << newSlot << endl;
                    }
                }
            }
        }

        // 3. View waiting queue
        else if (choice == 3) {
            displayQueue(waitingQueue);
        }

        // 4. Add to waiting queue manually
        else if (choice == 4) {
            string plate, time;
            cout << "Plate number: ";
            cin >> plate;
            cout << "Entry time (HH:MM): ";
            cin >> time;
            Vehicle v;
            v.plate = plate;
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
                    // Reverse a PARK = remove the vehicle
                    deleteByPlate(parkingList, last.v.plate);
                    deleteHT(ht, last.v.plate);
                    bstRoot = deleteBST(bstRoot, last.v.slotID);
                    slotOccupied[last.v.slotID] = false;
                    cout << "Undo PARK: Vehicle " << last.v.plate
                        << " removed from slot " << last.v.slotID << endl;
                } else if (last.actionType == "REMOVE") {
                    // Reverse a REMOVE = park the vehicle back
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
            Vehicle result;
            if (searchHT(ht, plate, result)) {
                cout << "Found -> Plate: " << result.plate
                    << " | Slot: " << result.slotID
                    << " | Entry Time: " << result.entryTime << endl;
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
            int sortChoice;
            cin >> sortChoice;
            if (sortChoice == 1) {
                sortByPlate(parkingList);
                cout << "Sorted by plate." << endl;
            } else if (sortChoice == 2) {
                sortBySlot(parkingList);
                cout << "Sorted by slot ID." << endl;
            } else if (sortChoice == 3) {
                sortByTime(parkingList);
                cout << "Sorted by entry time." << endl;
            } else {
                cout << "Invalid choice." << endl;
            }
            displayAll(parkingList);
        }

        // Browse slots by ID (BST in-order)
        else if (choice == 9) {
            cout << "All occupied slots in ascending order:" << endl;
            inOrder(bstRoot);
        }

        // 10. Save and Exit 
        else if (choice == 10) {
            saveToCSV(parkingList);
            cout << "Goodbye!" << endl;
        }

        else {
            cout << "Invalid choice. Please enter 1-10." << endl;
        }

    } while (choice != 10);

    return 0;
}