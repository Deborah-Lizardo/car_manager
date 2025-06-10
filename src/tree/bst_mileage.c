#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst_mileage.h"

Node* createNode(int price, char* model, int mileage) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error allocating node\n");
        return NULL;
    }
    newNode->price = price;
    strcpy(newNode->model, model);
    newNode->mileage = mileage;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insertByMileage(Node* root, int price, char* model, int mileage) {
    if (root == NULL) {
        return createNode(price, model, mileage);
    }
    if (mileage < root->mileage) {
        root->left = insertByMileage(root->left, price, model, mileage);
    } else {
        root->right = insertByMileage(root->right, price, model, mileage);
    }
    return root;
}

void printMileageTree(Node* root) {
    if (root != NULL) {
        printMileageTree(root->left);
        printf("Model: %s, Mileage: %d, Price: %d\n", root->model, root->mileage, root->price);
        printMileageTree(root->right);
    }
}
