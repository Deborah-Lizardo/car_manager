#include <stdio.h>
#include <stdlib.h>
#include "../include/year_list.h"

YearNode* insertYear(YearNode* list, int year, Car* car) {
    YearNode* current = list;
    YearNode* previous = NULL;

    // Find the correct position or existing year node
    while (current != NULL && current->year < year) {
        previous = current;
        current = current->next;
    }

    // If the year already exists, add the car to its car list
    if (current != NULL && current->year == year) {
        YearCarNode* newCarNode = malloc(sizeof(YearCarNode));
        newCarNode->car = car;
        newCarNode->next = current->carList;
        current->carList = newCarNode;
        return list;
    }

    // Create a new year node
    YearNode* newYearNode = malloc(sizeof(YearNode));
    newYearNode->year = year;
    newYearNode->carList = NULL;
    newYearNode->next = current;

    // Create the first car node for this year
    YearCarNode* newCarNode = malloc(sizeof(YearCarNode));
    newCarNode->car = car;
    newCarNode->next = NULL;
    newYearNode->carList = newCarNode;

    if (previous == NULL) {
        // Insert at the beginning of the list
        return newYearNode;
    } else {
        previous->next = newYearNode;
        return list;
    }
}

void displayCarsFromYear(YearNode* list, int minYear) {
    while (list != NULL) {
        if (list->year >= minYear) {
            YearCarNode* node = list->carList;
            while (node != NULL) {
                Car* c = node->car;
                printf("Brand: %s | Model: %s | Year: %d | Mileage: %d | Price: %.2f\n",
                       c->brand, c->model, c->year, c->km, c->price);
                node = node->next;
            }
        }
        list = list->next;
    }
}

void freeYearList(YearNode* list) {
    while (list != NULL) {
        YearNode* temp = list;
        list = list->next;

        YearCarNode* node = temp->carList;
        while (node != NULL) {
            YearCarNode* aux = node;
            node = node->next;
            free(aux);
        }

        free(temp);
    }
}
