#ifndef PRICE_TREE_H
#define PRICE_TREE_H
#include "car.h"

typedef struct PriceTree {
    int key;
    float price;
    Car* car;
    struct PriceTree* left;
    struct PriceTree* right;
} PriceTree;

PriceTree* insertPriceNode(PriceTree* root, float key, Car* car);
void searchPriceInterval(PriceTree* root, float min, float max);
void freePriceTree(PriceTree* root);

#endif