#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        // Check if the car already exists in the list for this year
        YearCarNode* carNode = current->CarList;
        while (carNode != NULL) {
            if (carNode->car == car) {  // Check if the car is already in the list
                return list;  // If the car already exists, return the list as is (no insertion)
            }
            carNode = carNode->next;
        }

        YearCarNode* newCarNode = malloc(sizeof(YearCarNode)); // Allocate memory for the new car node
        if (newCarNode == NULL) {
            printf("Memory allocation failed!\n");
            return list;
        }
        newCarNode->car = car;
        newCarNode->next = current->CarList; // Use CarList instead of carList
        current->CarList = newCarNode; // Link new car node to the CarList of the year node
        return list;
    }

    // Create a new year node if the year doesn't exist
    YearNode* newYearNode = malloc(sizeof(YearNode)); // Allocate memory for the new year node
    if (newYearNode == NULL) {
        printf("Memory allocation failed!\n");
        return list;
    }
    newYearNode->year = year;
    newYearNode->CarList = NULL; // Initialize the CarList as NULL
    newYearNode->next = current; // Link the new year node to the existing list

    // Create the first car node for this year
    YearCarNode* newCarNode = malloc(sizeof(YearCarNode)); // Allocate memory for the first car node
    if (newCarNode == NULL) {
        printf("Memory allocation failed!\n");
        free(newYearNode); // Free the year node if car node allocation fails
        return list;
    }
    newCarNode->car = car;
    newCarNode->next = NULL;
    newYearNode->CarList = newCarNode;

    if (previous == NULL) {
        return newYearNode;
    } else {
        previous->next = newYearNode;
        return list;
    }
}

// Function to display cars from a certain year or greater
void displayCarsFromYear(YearNode* list, int minYear) {
    while (list != NULL) {
        // Only display cars from the specified year or later
        if (list->year >= minYear) {
            printf("Cars from year %d or later:\n", list->year);
            YearCarNode* node = list->CarList;
            while (node != NULL) {
                Car* c = node->car;
                printf("Brand: %s | Model: %s | Year: %d | Mileage: %d| Price: %.2f\n",
                       c->brand, c->model, c->year, c->km, c->price);
                node = node->next;
            }
        }
        list = list->next;
    }
}

// Function to free the allocated memory for the year list
void freeYearList(YearNode* list) {
    while (list != NULL) {
        YearNode* temp = list;
        list = list->next;

        // Free all YearCarNode nodes
        YearCarNode* node = temp->CarList; // Use CarList instead of carList
        while (node != NULL) {
            YearCarNode* aux = node;
            node = node->next;
            free(aux); // Free each car node
        }

        free(temp);  // Free the year node itself
    }
}
