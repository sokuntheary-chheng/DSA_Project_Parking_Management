#include <iostream>
#include "stack.h"

using namespace std;
Stack* createEmptyStack() {
    Stack* st = new Stack;
    st->n = 0;
    st->top = nullptr;
    return st;
}

void push(Stack* st, ActionRecord a) {
    StackElement* e = new StackElement;
    e->data = a;
    e->next = st->top;
    st->top = e;
    st->n++;
}

ActionRecord pop(Stack* st) {
    if (st->n == 0 || st->top == nullptr) {
        cout << "Stack is empty. Nothing to undo." << endl;
        ActionRecord empty; 
        empty.actionType = "";
        return empty;
    }
    StackElement* tmp = st->top;
    ActionRecord a = tmp->data;
    st->top = tmp->next;
    delete tmp;
    st->n--;
    return a;
}

ActionRecord peek(Stack* st) {
    if (st->n == 0 || st->top == nullptr) {
        ActionRecord empty; 
        empty.actionType = "";
        return empty;
    }
    return st->top->data;
}

bool isEmptyStack(Stack* st) {
    return st->n == 0;
}

void displayStack(Stack* st) {
    if (st->n == 0 || st->top == nullptr) {
        cout << "No actions in history." << endl;
        return;
    }
    cout << "\n--- Action History (Top to Bottom) ---" << endl;
    StackElement* current = st->top;
    while (current != nullptr) {
        cout << "Action: " << current->data.actionType 
             << " | Plate: " << current->data.v.plate 
             << " | Slot: " << current->data.v.slotID << endl;
        current = current->next;
    }
    cout << "---------------------------------------" << endl;
}