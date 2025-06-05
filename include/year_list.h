#ifndef YEAR_LIST_H
#define YEAR_LIST_H
#include "car.h"

typedef struct YearNode {
    int year;
    struct YearCarNode *CarList;
    struct YearNode* next;
} YearNode;

typedef struct YearCarNode { // lista enc ordenada por ano
    Car* car;
    struct YearCarNode* next;
} YearCarNode;

YearCarNode* InsertNewCar(YearCarNode* root, Car* car);
void PrintYearCar (YearCarNode* carlist);
void freeYearList(YearNode* list);

#endif