#ifndef FILEIO_H
#define FILEIO_H
#include "linkedlist.h"
#include "hashtable.h"
#include "bst.h"

void saveToCSV(List* ls);
void loadFromCSV(List* ls, HashTable* ht, BSTNode** bstRoot);

#endif