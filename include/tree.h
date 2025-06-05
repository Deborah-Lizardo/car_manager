// tree.h
#ifndef TREE_H
#define TREE_H

#include "car.h"

typedef Car car;

typedef struct TreeNode {
    float key;       // Can be mileage or price
     Car* car;      // Pointer to the corresponding car in the array
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Basic functions
TreeNode* insertTree(TreeNode* root, float key,  Car* car);
void searchInterval(TreeNode* root, float min, float max);
void freeTree(TreeNode* root);

#endif
