#include <stdio.h>
#include <stdlib.h>
#include "../include/mil_tree.h"

// Insert function: Adds a new node to the tree
MileageTree* insertNode(MileageTree* root, int key, Car* car) {
    if (car == NULL) {
        printf("Car pointer is NULL!\n");
        return root;
    }
    // If the tree is empty, allocate memory for a new node
    if (root == NULL) {
        root = (MileageTree*)malloc(sizeof(MileageTree));
        if (root == NULL) {
            printf("Memory allocation failed!\n");
            return NULL;
        }
        root->key = key;
        root->left = NULL;
        root->right = NULL;
    } else if (key < root->key) {
        // If the key is smaller, insert into the left subtree
        root->left = insertNode(root->left, key, car);
    } else {
        // If the key is larger, insert into the right subtree
        root->right = insertNode(root->right, key, car);
    }
    return root;
}
// Search function that find cars within a mileage range
void searchInterval(MileageTree* root, int min, int max, int* found) {
    if (root == NULL) {
        return;
    }
    if (root->key >= min && root->key <= max) {
        printf("Car found: %s, Model: %s, Year: %d, Mileage: %d, Price: %.2f\n",
               root->car->brand, root->car->model, root->car->year, root->car->km, root->car->price);
        *found = 1;  // Set the found flag to indicate at least one car was found
    }
    // If the current node's mileage is greater than the minimum, search in the left subtree
    if (root->key > min) {
        searchInterval(root->left, min, max, found);
    }
    // If the current node's mileage is less than the maximum, search in the right subtree
    if (root->key < max) {
        searchInterval(root->right, min, max, found);
    }
}
// Public search function
void search(MileageTree* root, int min, int max) {
    int found = 0;  // Indicator of whether any cars were found
    searchInterval(root, min, max, &found);

    // If no cars were found within the range, print a message
    if (!found) {
        printf("No cars found within the mileage range [%d, %d].\n", min, max);
    }
}
// Function to destroy the tree and free the allocated memory
void destroyTree(MileageTree* root) {
    if (root == NULL) {
        return;
    }
    // Recursively destroy the left and right subtrees
    destroyTree(root->left);
    destroyTree(root->right);
    // Free the memory allocated for the current node
    free(root);
}
