#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

BSTNode* insertBST(BSTNode* root, Vehicle v) {
    if (root == nullptr) {
        BSTNode* node = new BSTNode;
        node->data = v;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }
    if (v.slotID < root->data.slotID) {
        root->left = insertBST(root->left, v);
    } else if (v.slotID > root->data.slotID) {
        root->right = insertBST(root->right, v);
    }
    return root;
}

BSTNode* searchBST(BSTNode* root, int slotID) {
    if (root == nullptr) return nullptr;
    if (slotID == root->data.slotID) return root;
    if (slotID < root->data.slotID) {
        return searchBST(root->left, slotID);
    }
    return searchBST(root->right, slotID);
}

BSTNode* findMin(BSTNode* root) {
    if (root == nullptr) return nullptr;
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

BSTNode* deleteBST(BSTNode* root, int slotID) {
    if (root == nullptr) return nullptr;
    
    if (slotID < root->data.slotID) {
        root->left = deleteBST(root->left, slotID);
    } else if (slotID > root->data.slotID) {
        root->right = deleteBST(root->right, slotID);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        } else if (root->left == nullptr) {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        } else {
            BSTNode* minNode = findMin(root->right);
            root->data = minNode->data;
            root->right = deleteBST(root->right, minNode->data.slotID);
        }
    }
    return root;
}

void inOrder(BSTNode* root) {
    if (root != nullptr) {
        inOrder(root->left);
        cout << "Slot " << root->data.slotID << " | Plate: " << root->data.plate 
             << " | Type: " << root->data.type << " | Time: " << root->data.entryTime << endl;
        inOrder(root->right);
    }
}

void preOrder(BSTNode* root) {
    if (root != nullptr) {
        cout << "Slot " << root->data.slotID << " | Plate: " << root->data.plate 
             << " | Type: " << root->data.type << " | Time: " << root->data.entryTime << endl;
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(BSTNode* root) {
    if (root != nullptr) {
        postOrder(root->left);
        postOrder(root->right);
        cout << "Slot " << root->data.slotID << " | Plate: " << root->data.plate 
             << " | Type: " << root->data.type << " | Time: " << root->data.entryTime << endl;
    }
}

int countBST(BSTNode* root) {
    if (root == nullptr) return 0;
    return 1 + countBST(root->left) + countBST(root->right);
}