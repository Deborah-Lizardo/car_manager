#ifndef YEAR_LIST_H
#define YEAR_LIST_H
#include "car.h"

typedef struct YearNode {
    int year;
    struct YearCarNode *CarList;
    struct YearNode* next;
} YearNode;

typedef struct YearCarNode {
    Car* car;
    struct YearCarNode* next;
} YearCarNode;

YearCarNode* InsertNewCar(YearCarNode* root, Car* car);
void PrintYearCar (YearCarNode* carlist);
void freeYearList(YearNode* list);

YearNode* insertYear(YearNode* list, int year, Car* car);
void displayCarsFromYear(YearNode* list, int minYear);
void freeYearList(YearNode* list);

#endif