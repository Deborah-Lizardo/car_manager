#ifndef MIL_TREE_H
#define MIL_TREE_H
#include "car.h"

typedef Car car;

typedef struct MileageTree {
    int key;
    Car* car;
    int found;
    struct MileageTree* left;
    struct MileageTree* right;
} MileageTree;

// Functions
MileageTree* insertNode(MileageTree* root, int key,  Car* car);
void searchInterval(MileageTree* root, int min, int max, int* found);
void freeTree(MileageTree* root);
void search(MileageTree* root, int min, int max);

#endif
