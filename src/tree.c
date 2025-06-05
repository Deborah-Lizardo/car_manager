// tree.c
#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"

TreeNode* insertTree(TreeNode* root, float key, Car* car) {
    if (root == NULL) {
        TreeNode* newNode = (TreeNode*) malloc(sizeof(TreeNode));
        newNode->key = key;
        newNode->car = car;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (key < root->key)
        root->left = insertTree(root->left, key, car);
    else
        root->right = insertTree(root->right, key, car);

    return root;
}

void searchInterval(TreeNode* root, float min, float max) {
    if (root == NULL)
        return;

    if (root->key >= min)
        searchInterval(root->left, min, max);

    if (root->key >= min && root->key <= max) {
        printf("Brand: %s | Model: %s | Year: %d | Mileage: %d | Price: %.2f\n",
               root->car->brand, root->car->model,
               root->car->year, root->car->mileage, root->car->price);
    }

    if (root->key <= max)
        searchInterval(root->right, min, max);
}

void freeTree(TreeNode* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
