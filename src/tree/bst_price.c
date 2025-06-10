#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst_price.h"

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

Node* insertByPrice(Node* root, int price, char* model, int mileage) {
    if (root == NULL) {
        return createNode(price, model, mileage);
    }
    if (price < root->price) {
        root->left = insertByPrice(root->left, price, model, mileage);
    } else {
        root->right = insertByPrice(root->right, price, model, mileage);
    }
    return root;
}

void printPriceTree(Node* root) {
    if (root != NULL) {
        printPriceTree(root->left);
        printf("Model: %s, Price: %d, Mileage: %d\n", root->model, root->price, root->mileage);
        printPriceTree(root->right);
    }
}
