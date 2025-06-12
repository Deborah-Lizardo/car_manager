#include <stdio.h>
#include <stdlib.h>
#include "../include/mil_tree.h"

// Function to create a new node in the mileage tree
MileageTree* createMileageNode(int key, Car* car) {
    // Allocate memory for a new node
    MileageTree* newNode = (MileageTree*) malloc(sizeof(MileageTree));

    // Check for memory allocation failure
    if (newNode == NULL) {
        printf("Error allocating node\n");
        return NULL;
    }

    // Initialize the node with the given key (mileage) and the car data
    newNode->key = key;    // Mileage is used as the key for comparison
    newNode->car = car;    // Store the car's details
    newNode->found = 0;    // Set the found flag to 0 (not found initially)
    newNode->left = NULL;  // Initialize left child as NULL
    newNode->right = NULL; // Initialize right child as NULL

    return newNode;
}

// Function to insert a car in the mileage tree
MileageTree* insertNodeKm(MileageTree* root, int key, Car* car) {
    // If the root is NULL, we create a new node and return it
    if (root == NULL) {
        return createMileageNode(key, car);
    }

    // Compare the mileage and decide whether to insert into the left or right subtree
    if (key < root->key) {
        root->left = insertNodeKm(root->left, key, car); // Insert in the left subtree
    } else {
        root->right = insertNodeKm(root->right, key, car); // Insert in the right subtree
    }

    return root;
}
#include <stdio.h>
#include <stdlib.h>
#include "../include/mil_tree.h"

// Function to search cars by mileage range
void searchMileage(MileageTree* root, int min, int max) {
    // Print the header for the table only once
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
        // Check if the car's mileage is within the range
        if (root->key >= min && root->key <= max) {
            // Print the matching car's information
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

    // If the current node is not NULL, print its details
    if (root != NULL) {
        printMileageTree(root->left);  // Visit the left subtree
        // Print the car's details stored in the node
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

    // Recursively free the left and right subtrees
    freeKmTree(root->left);
    freeKmTree(root->right);

    // Free the memory allocated for the current node
    free(root);
}
