#ifndef PRICE_TREE_H
#define PRICE_TREE_H
#include "car.h"

typedef Car car;

typedef struct PriceTree {
    float km;
    Car* car;
    struct PriceTree* left;
    struct PriceTree* right;
} PriceTree;

// Functions
PriceTree *insertNode(PriceTree *root, float key, Car *car);
void searchInterval(PriceTree *root, float min, float max);
void freeTree(PriceTree *root);

#endif
