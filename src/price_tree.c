#include <stdio.h>
#include <stdlib.h>
#include "price_tree.h"

PriceTree* insertPriceNode(PriceTree* root, float key, Car* car) {
    if (car == NULL) {
        printf("Car pointer is NULL!\n");
        return root;
    }

    if (root == NULL) {
        root = (PriceTree*)malloc(sizeof(PriceTree));
        if (root == NULL) {
            printf("Memory allocation failed!\n");
            return NULL;
        }
        root->price = key;
        root->car = car;
        root->left = NULL;
        root->right = NULL;
    } else if (key < root->price) {
        root->left = insertPriceNode(root->left, key, car);
    } else {
        root->right = insertPriceNode(root->right, key, car);
    }
    return root;
}

void searchPriceInterval(PriceTree* root, float min, float max) {
    if (root == NULL) return;

    if (root->price >= min && root->price <= max) {
        printf("Car found: %s, Model: %s, Year: %d, Mileage: %d, Price: %.2f\n",
               root->car->brand, root->car->model, root->car->year, root->car->km, root->car->price);
    }
    if (root->price > min) searchPriceInterval(root->left, min, max);
    if (root->price < max) searchPriceInterval(root->right, min, max);
}

void freePriceTree(PriceTree* root) {
    if (root == NULL) return;
    freePriceTree(root->left);
    freePriceTree(root->right);
    free(root);
}