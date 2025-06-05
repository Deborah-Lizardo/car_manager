#ifndef YEAR_LIST_H
#define YEAR_LIST_H

#include "car.h"

typedef struct YearCarNode {
    Car* car; // pointer to the car in the array
    struct YearCarNode* next;
} YearCarNode;

typedef struct YearNode {
    int year;
    YearCarNode* carList; // list of cars for this year
    struct YearNode* next;
} YearNode;

YearNode* insertYear(YearNode* list, int year, Car* car);
void displayCarsFromYear(YearNode* list, int minYear);
void freeYearList(YearNode* list);

#endif
