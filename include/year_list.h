#ifndef YEAR_LIST_H
#define YEAR_LIST_H
#include "car.h"

typedef struct YearNode {//O nó da lista de anos contém o ano e um ponteiro para a lista de carros year
    int year;
    struct YearCarNode *CarList;
    struct YearNode* next;
} YearNode;

typedef struct YearCarNode { //cada no da lista de carros
    Car* car;//ponteiro para o vetor de carros
    struct YearCarNode* next;
} YearCarNode;

YearCarNode* InsertNewCar(YearCarNode* root, Car* car);
void PrintYearCar (YearCarNode* carlist);
void freeYearList(YearNode* list);

YearNode* insertYear(YearNode* list, int year, Car* car);
void displayCarsFromYear(YearNode* list, int minYear);
void freeYearList(YearNode* list);

#endif