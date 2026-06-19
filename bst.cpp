#include <iostream>
#include "bst.h"
using namespace std;

BSTNode* insertBST(BSTNode* root, Vehicle v) {
    if (root == nullptr) {
        BSTNode* node = new BSTNode;
        node->data = v;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }
    if (v.slotID < root->data.slotID)
        root->left = insertBST(root->left, v);
    else if (v.slotID > root->data.slotID)
        root->right = insertBST(root->right, v);
    return root;
}

void inOrder(BSTNode* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << "Slot " << root->data.slotID
            << " | Plate: " << root->data.plate
            << " | Time: " << root->data.entryTime << endl;
        inOrder(root->right);
    }
}

BSTNode* searchBST(BSTNode* root, int slotID) {
    if (root == nullptr) return nullptr;
    if (slotID == root->data.slotID) return root;
    if (slotID < root->data.slotID) return searchBST(root->left, slotID);
    return searchBST(root->right, slotID);
}

// Helper: find minimum node in a subtree (for delete case 3)
BSTNode* findMin(BSTNode* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

BSTNode* deleteBST(BSTNode* root, int slotID) {
    if (root == nullptr) {
        cout << "Slot " << slotID << " not found in BST." << endl;
        return nullptr;
    }
    if (slotID < root->data.slotID) {
        root->left = deleteBST(root->left, slotID);
    } else if (slotID > root->data.slotID) {
        root->right = deleteBST(root->right, slotID);
    } else {
        // Case 1: no children
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // Case 2: one child
        if (root->left == nullptr) {
            BSTNode* tmp = root->right;
            delete root;
            return tmp;
        }
        if (root->right == nullptr) {
            BSTNode* tmp = root->left;
            delete root;
            return tmp;
        }
        // Case 3: two children — find min in right subtree
        BSTNode* minNode = findMin(root->right);
        root->data = minNode->data;
        root->right = deleteBST(root->right, minNode->data.slotID);
    }
    return root;
}