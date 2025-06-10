#include <stdio.h>
#include "bst_price.h"   // ou o arquivo que declara Node
#include "bst_mileage.h" // se Node estiver lá, ajuste conforme seu projeto

void filterByPrice(Node* root, int minPrice, int maxPrice) {
    if (root == NULL) return;

    filterByPrice(root->left, minPrice, maxPrice);

    if (root->price >= minPrice && root->price <= maxPrice) {
        printf("Model: %s, Price: %d, Mileage: %d\n", root->model, root->price, root->mileage);
    }

    filterByPrice(root->right, minPrice, maxPrice);
}

void filterByMileage(Node* root, int minMileage, int maxMileage) {
    if (root == NULL) return;

    filterByMileage(root->left, minMileage, maxMileage);

    if (root->mileage >= minMileage && root->mileage <= maxMileage) {
        printf("Model: %s, Mileage: %d, Price: %d\n", root->model, root->mileage, root->price);
    }

    filterByMileage(root->right, minMileage, maxMileage);
}
