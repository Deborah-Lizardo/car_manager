#ifndef PRICE_TREE_H
#define PRICE_TREE_H
#include "car.h"

typedef struct PriceTree {
    float price;
    int key;// Flag to indicate if the car was found
    Car* car;
    struct PriceTree* left;
    struct PriceTree* right;
} PriceTree;

PriceTree* insertPriceNode(PriceTree* root, float key, Car* car);
void searchPrice(PriceTree* root, float min, float max);
void freePriceTree(PriceTree* root);
void checkIfFoundPrice(int found);
#endif