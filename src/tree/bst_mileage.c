#include <stdio.h>
#include <stdlib.h>
#include "../include/mil_tree.h"

MileageTree* createMileageNode(int key, Car* car) { // Function to create a new node in the mileage tree
    // Allocate memory for a new node
    MileageTree* newNode = (MileageTree*) malloc(sizeof(MileageTree));
    // Check for memory allocation failure
    if (newNode == NULL) {
        printf("Error allocating node\n");
        return NULL;
    }
    // Initialize the node with the given key (mileage) and the car data
    newNode->key = key;
    newNode->car = car;
    newNode->found = 0;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Function to insert a car in the mileage tree
MileageTree* insertNodeKm(MileageTree* root, int key, Car* car) {
    if (root == NULL) {
        return createMileageNode(key, car);
    }
    // Compare the mileage and decide whether to insert into the left or right subtree
    if (key < root->key) {
        root->left = insertNodeKm(root->left, key, car);
    } else {
        root->right = insertNodeKm(root->right, key, car);
    }
    return root;
}

// Function to search cars by mileage range
void searchMileage(MileageTree* root, int min, int max) {
    static int headerPrinted = 0;  // Flag to print header only once

    if (!headerPrinted) {
        printf("\nDisplaying cars within mileage range [%d - %d]:\n", min, max);
        printf("-------------------------------------------------------------\n");
        printf("| %-10s | %-10s | %-4s | %-8s | %-8s |\n", "Brand", "Model", "Year", "Mileage", "Price");
        printf("-------------------------------------------------------------\n");
        headerPrinted = 1;  // Set the flag to prevent further header printing
    }
    // Traverse the tree and print matching cars
    if (root != NULL) {
        if (root->key >= min && root->key <= max) {
            printf("| %-10s | %-10s | %-4d | %-8d | $%-7.2f |\n", root->car->brand, root->car->model, root->car->year, root->key, root->car->price);
        }

        // Recursively search left and right subtrees
        if (min < root->key) {
            searchMileage(root->left, min, max);
        }
        if (max > root->key) {
            searchMileage(root->right, min, max);
        }
    }
}
// Function to check if any car was found in the given mileage range
void checkIfFoundMileage(int found) {
    if (found == 0) {
        printf("No cars found in this mileage range.\n");
    } else {
        printf("Cars found in the specified mileage range.\n");
    }
}
// Function to print all the cars in the mileage tree (in-order traversal)
void printMileageTree(MileageTree* root) {
    printf("\nDisplaying all cars in the mileage tree:\n");
    printf("----------------------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-6s | %-10s |\n", "Brand", "Model", "Year", "Mileage");
    printf("----------------------------------------------------------------------------------\n");

    if (root != NULL) {
        printMileageTree(root->left);  // Visit the left subtree
        printf("| %-15s | %-15s | %-6d | %-10d |\n", root->car->brand, root->car->model, root->car->year, root->key);
        printMileageTree(root->right); // Visit the right subtree
    }
}
// Function to free the memory allocated for the mileage tree
void freeKmTree(MileageTree* root) {
    // Base case: If the root is NULL, return
    if (root == NULL) {
        return;
    }
    freeKmTree(root->left);
    freeKmTree(root->right);
    free(root);
}
