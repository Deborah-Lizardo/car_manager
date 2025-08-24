#include <stdio.h>
#include <stdlib.h>
#include "../include/price_tree.h"
#include "../include/list.h"

// Function to create a new node for the price tree
PriceTree* createPriceNode(float price, Car* car) {
    PriceTree* newNode = (PriceTree*) malloc(sizeof(PriceTree));
    if (newNode == NULL) {
        printf("Error allocating node\n");
        return NULL;
    }
    newNode->price = price;
    newNode->car = car;
    newNode->key = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a car into the tree based on its price
PriceTree* insertPriceNode(PriceTree* root, float price, Car* car) {
    if (root == NULL) {
        return createPriceNode(price, car);
    }
    if (price < root->price) {
        root->left = insertPriceNode(root->left, price, car);
    } else {
        root->right = insertPriceNode(root->right, price, car);
    }
    return root;
}
// Function to search cars by price range
void searchPrice(PriceTree* root, float min, float max) {
    static int headerPrinted = 0;  // Flag to print header only once

    if (!headerPrinted) {
        printf("| %-10s | %-10s | %-4s | %-8s | %-8s |\n", "Brand", "Model", "Year", "Mileage", "Price");
        printf("-------------------------------------------------------------\n");
        headerPrinted = 1;
    }

    // Traverse the tree and print matching cars
    if (root != NULL) {
        if (root->price >= min && root->price <= max) {
            printf("| %-10s | %-10s | %-4d | %-8d | $%-7.2f |\n", root->car->brand, root->car->model, root->car->year, root->car->km, root->price);
        }
        if (min < root->price) {
            searchPrice(root->left, min, max);
        }
        if (max > root->price) {
            searchPrice(root->right, min, max);
        }
    }
}

void printPriceTree(PriceTree* root) {
    printf("\nDisplaying all cars in the price tree:\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-6s | %-10s | %-12s |\n", "Brand", "Model", "Year", "Mileage", "Price");
    printf("----------------------------------------------------------------------------------\n");

    if (root != NULL) {
        printPriceTree(root->left);
        printf("| %-15s | %-15s | %-6d | %-10d | $%-12.2f |\n", root->car->brand, root->car->model, root->car->year, root->car->km, root->price);
        printPriceTree(root->right); // Visit the right subtree
    }
}
// Function to free the allocated memory for the price tree
void freePriceTree(PriceTree* root) {
    if (root == NULL) {
        return;
    }
    freePriceTree(root->left);
    freePriceTree(root->right);
    free(root);
}
