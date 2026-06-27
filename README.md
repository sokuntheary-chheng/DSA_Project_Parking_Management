# Parking Management System

A console-based C++ application that simulates a university parking lot, built for the Data Structure and Algorithms team project (DSA Team 11).

## Team Members

| Name | Student ID | Role |
|---|---|---|
| Chheng Sokuntheary | p20240044 | Member A — Linked List, Sorting, System Integration |
| Chin Menghong | p20240024 | Member B — Stack, Queue, File I/O |
| Dara Panhaseth | p22040002 | Member C — Hash Table, Binary Search Tree |

## Project Overview

This system manages a university parking lot with:
- 10 car slots (Slot ID 1-10)
- 290 motorcycle slots (Slot ID 11-300)
- Total capacity: 300 slots

Data is persisted to `parking_data.csv` so records are not lost between runs.

## Data Structures Used

| Data Structure | Purpose | Implemented By |
|---|---|---|
| Singly Linked List | Stores all parked vehicle records | Member A |
| Sorting (Bubble Sort) | Sorts vehicles by plate, slot, or entry time | Member A |
| Stack | Undo the most recent park/remove action, view action history | Member B |
| Queue | Holds vehicles waiting for a free slot | Member B |
| Hash Table (Separate Chaining) | Fast O(1) average vehicle search and update by plate number | Member C |
| Binary Search Tree | Browses parking slots in sorted order by Slot ID, counts total vehicles | Member C |

## Features (CRUD + Required Functionality)

| # | Feature | CRUD Operation | Data Structure |
|---|---|---|---|
| 1 | Park a vehicle (Car or Motorcycle) | Create | Linked List + Hash Table + BST + Stack |
| 2 | Remove a vehicle | Delete | Linked List + Hash Table + BST + Stack |
| 3 | View waiting queue | Read | Queue |
| 4 | Add vehicle to waiting queue | Create | Queue |
| 5 | Undo last action | - | Stack |
| 6 | Search vehicle by plate | Read | Hash Table |
| 7 | Display all parked vehicles | Read | Linked List |
| 8 | Sort vehicles (plate, slot, or time) | - | Sorting (Bubble Sort) |
| 9 | Browse slots in order (in-order traversal) | Read | BST |
| 10 | Update vehicle entry time | Update | Linked List + Hash Table |
| 11 | View recent action history | Read | Stack |
| 12 | Peek next vehicle in waiting queue | Read | Queue |
| 13 | View BST pre-order / post-order traversal | Read | BST |
| 14 | Display hash table contents (bucket view) | Read | Hash Table |
| 15 | Count total parked vehicles | Read | BST |
| 16 | Save and exit | - | File I/O |

## Repository Structure

```
DSA_PROJECT/
├── DSA_Team11_Parking_Management_System_Report.docx   # Project report (Word)
├── DSA_Team11_Parking_Management_System_Report.pdf    # Project report (PDF)
├── Project_Flowchart.pdf                               # System flowchart
├── README.md
└── Source_Code/
    ├── vehicle.h          # Shared Vehicle struct
    ├── linkedlist.h/.cpp  # Linked list operations
    ├── sorting.h/.cpp     # Bubble sort implementations
    ├── stack.h/.cpp       # Stack for undo and action history
    ├── queue.h/.cpp       # Queue for waiting vehicles
    ├── hashtable.h/.cpp   # Hash table for fast search and update
    ├── bst.h/.cpp         # Binary search tree for sorted slot view
    ├── fileio.h/.cpp      # CSV save and load
    └── main.cpp           # Menu and system integration
```

> Compiled binaries (`*.exe`, `*.o`) and `parking_data.csv` are generated at runtime and are not required for grading the source code itself.

## How to Compile

Run this from inside the `Source_Code` folder:

```bash
cd Source_Code
g++ main.cpp linkedlist.cpp sorting.cpp stack.cpp queue.cpp fileio.cpp hashtable.cpp bst.cpp -o parking
```

## How to Run

**Windows:**
```bash
.\parking.exe
```

**Mac/Linux:**
```bash
./parking
```

## Complexity Summary

| Operation | Average Case | Worst Case |
|---|---|---|
| Linked list insert/delete | O(1) / O(n) | O(n) |
| Bubble sort | O(n) best, O(n^2) avg | O(n^2) |
| Stack push/pop/peek | O(1) | O(1) |
| Queue enqueue/dequeue/peek | O(1) | O(1) |
| Hash table search/insert/delete/update | O(1) average | O(n) |
| BST search/insert/delete | O(log n) average | O(n) |
| BST traversal (in/pre/post-order) | O(n) | O(n) |

## Known Limitations

- The waiting queue is not saved to `parking_data.csv`. Only parked vehicles persist between sessions; any vehicle still waiting in the queue when the program closes is not restored on the next run.
- When a freed slot does not match the vehicle type at the front of the waiting queue, that vehicle is re-added to the back of the queue rather than keeping its original position.
- Plate matching is case-sensitive.
- The binary search tree is not self-balancing, so its worst-case performance depends on the order in which vehicles are parked.

## Academic Integrity

All code in this repository was written independently by the team members listed above, following concepts taught in the Data Structure and Algorithms course (Lessons 04-13). No AI-generated or copied code was used in the implementation.

## Course Information

- **Course:** Data Structure and Algorithms
- **Lecturer:** Seak Leng
- **Team:** DSA Team 11
- **Deadline:** June 30, 2026