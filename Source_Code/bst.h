#ifndef BST_H
#define BST_H
#include "vehicle.h"

struct BSTNode {
    Vehicle data;
    BSTNode* left;
    BSTNode* right;
};

BSTNode* insertBST(BSTNode* root, Vehicle v);
BSTNode* searchBST(BSTNode* root, int slotID);
BSTNode* deleteBST(BSTNode* root, int slotID);
void inOrder(BSTNode* root);
void preOrder(BSTNode* root);
void postOrder(BSTNode* root);
int countBST(BSTNode* root);

#endif