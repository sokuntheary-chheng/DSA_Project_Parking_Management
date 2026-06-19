#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string>
#include "vehicle.h"

using namespace std;

struct ActionRecord {
    string actionType; 
    Vehicle v;
};

struct StackElement {
    ActionRecord data;
    StackElement* next;
};

struct Stack {
    int n;
    StackElement* top;
};

Stack* createEmptyStack();
void push(Stack* st, ActionRecord a);
ActionRecord pop(Stack* st);
ActionRecord peek(Stack* st);
bool isEmptyStack(Stack* st);
void displayStack(Stack* st);

#endif