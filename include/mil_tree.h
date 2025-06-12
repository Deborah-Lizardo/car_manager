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
MileageTree* insertNodeKm(MileageTree* root, int key,  Car* car);
void searchMileage(MileageTree* root, int min, int max);
void freeKmTree(MileageTree* root);
void checkIfFoundMileage(int found);
#endif
