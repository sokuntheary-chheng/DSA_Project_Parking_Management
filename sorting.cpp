#include "sorting.h"
#include "linkedlist.h"

// ─── Sort by License Plate (alphabetical ascending) ───────────────────────────
void sortByPlate(List* ls) {
    if (ls->n < 2) return;
    bool swapped;
    Element* end = nullptr;
    do {
        swapped = false;
        Element* current = ls->head;
        while (current->next != end) {
            if (current->data.plate > current->next->data.plate) {
                Vehicle temp   = current->data;
                current->data  = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
        end = current;
    } while (swapped);
}

// ─── Sort by Slot ID (numeric ascending) ──────────────────────────────────────
void sortBySlot(List* ls) {
    if (ls->n < 2) return;
    bool swapped;
    Element* end = nullptr;
    do {
        swapped = false;
        Element* current = ls->head;
        while (current->next != end) {
            if (current->data.slotID > current->next->data.slotID) {
                Vehicle temp   = current->data;
                current->data  = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
        end = current;
    } while (swapped);
}

// ─── Sort by Entry Time (chronological ascending) ─────────────────────────────
void sortByTime(List* ls) {
    if (ls->n < 2) return;
    bool swapped;
    Element* end = nullptr;
    do {
        swapped = false;
        Element* current = ls->head;
        while (current->next != end) {
            if (current->data.entryTime > current->next->data.entryTime) {
                Vehicle temp   = current->data;
                current->data  = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
        end = current;
    } while (swapped);
}