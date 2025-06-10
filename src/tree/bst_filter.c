#include <stdio.h>
#include "../include/bst_filter.h"
#include "../include/mil_tree.h"
#include "../include/price_tree.h"

// Function to filter by price in the binary search tree
void filterByPrice(PriceTree* root, float minPrice, float maxPrice) {
    // If the current node is NULL, just return
    if (root == NULL) return;

    // Recursively traverse the left subtree
    filterByPrice(root->left, minPrice, maxPrice);

    // Check if the car's price is within the specified range
    if (root->price >= minPrice && root->price <= maxPrice) {
        // Print the car's details if it matches the criteria
        printf("Model: %s, Price: %.2f, Mileage: %d\n", root->car->model, root->price, root->car->km);
    }

    // Recursively traverse the right subtree
    filterByPrice(root->right, minPrice, maxPrice);
}

// Function to filter by mileage in the binary search tree
void filterByMileage(MileageTree* root, int minMileage, int maxMileage) {
    // If the current node is NULL, just return
    if (root == NULL) return;

    // Recursively traverse the left subtree
    filterByMileage(root->left, minMileage, maxMileage);

    // Check if the car's mileage is within the specified range
    if (root->car->km >= minMileage && root->car->km <= maxMileage) {
        // Print the car's details if it matches the criteria
        printf("Model: %s, Mileage: %d, Price: %.2f\n", root->car->model, root->car->km, root->car->price);
    }

    // Recursively traverse the right subtree
    filterByMileage(root->right, minMileage, maxMileage);
}
