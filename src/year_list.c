#include <stdio.h>
#include <stdlib.h>
#include "../include/year_list.h"

// Function to insert a car into the YearNode list
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
        YearCarNode* newCarNode = (YearCarNode*)malloc(sizeof(YearCarNode));
        if (newCarNode == NULL) {
            printf("Memory allocation failed!\n");
            return list;
        }
        newCarNode->car = car;
        newCarNode->next = current->CarList;
        current->CarList = newCarNode;
        return list;
    }

    // Create a new year node
    YearNode* newYearNode = (YearNode*)malloc(sizeof(YearNode));
    if (newYearNode == NULL) {
        printf("Memory allocation failed!\n");
        return list;
    }
    newYearNode->year = year;
    newYearNode->CarList = NULL;
    newYearNode->next = current;

    // Create the first car node for this year
    YearCarNode* newCarNode = (YearCarNode*)malloc(sizeof(YearCarNode));
    if (newCarNode == NULL) {
        printf("Memory allocation failed!\n");
        return list;
    }
    newCarNode->car = car;
    newCarNode->next = NULL;
    newYearNode->CarList = newCarNode;

    if (previous == NULL) {
        // Insert at the beginning of the list
        return newYearNode;
    } else {
        previous->next = newYearNode;
        return list;
    }
}
// Function to display cars from a certain year or greater
void displayCarsFromYear(YearNode* list, int minYear) {
    while (list != NULL) {
        if (list->year >= minYear) {
            printf("Cars from year %d or later:\n", list->year);
            YearCarNode* node = list->CarList;
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
// Function to free the memory allocated for the year list
void freeYearList(YearNode* list) {
    while (list != NULL) {
        YearNode* temp = list;
        list = list->next;

        // Free all YearCarNode nodes
        YearCarNode* node = temp->CarList;
        while (node != NULL) {
            YearCarNode* aux = node;
            node = node->next;
            free(aux);  // Free the individual car nodes
        }

        free(temp);  // Free the year node itself
    }
}
