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
            if (strcmp(carNode->car->model, car->model) == 0 &&
                strcmp(carNode->car->brand, car->brand) == 0 &&
                carNode->car->year == car->year) {
                return list; // The car already exists, do not add
            }
            carNode = carNode->next;
        }

        // Insert the car into the car list for this year
        YearCarNode* newCarNode = malloc(sizeof(YearCarNode));
        if (newCarNode == NULL) {
            printf("Memory allocation failed!\n");
            return list;
        }
        newCarNode->car = car;
        newCarNode->next = current->CarList; // Link the new car to the car list
        current->CarList = newCarNode; // Update the car list
        return list;
    }

    // If the year does not exist, create a new year node
    YearNode* newYearNode = malloc(sizeof(YearNode));
    if (newYearNode == NULL) {
        printf("Memory allocation failed!\n");
        return list;
    }
    newYearNode->year = year;
    newYearNode->CarList = NULL; // Initialize the car list as NULL
    newYearNode->next = current; // Link the new year node to the existing list

    // Create the first car node for this year
    YearCarNode* newCarNode = malloc(sizeof(YearCarNode));
    if (newCarNode == NULL) {
        printf("Memory allocation failed!\n");
        free(newYearNode); // Free the year node if car node allocation fails
        return list;
    }
    newCarNode->car = car;
    newCarNode->next = NULL;
    newYearNode->CarList = newCarNode; // The car list now has the new car

    // Insert the year node into the list
    if (previous == NULL) {
        return newYearNode; // Add to the beginning of the list
    } else {
        previous->next = newYearNode; // Insert the new node at the correct position
        return list;
    }
}

// Function to display cars from a certain year or greater
void displayCarsFromYear(YearNode* list, int minYear) {
    printf("\nDisplaying cars from year %d or later:\n", minYear);
    printf("---------------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-6s | %-10s | %-12s |\n", "Brand", "Model", "Year", "Mileage", "Price");
    printf("---------------------------------------------------------------------------\n");

    int found = 0; // Flag to check if any car is found for the given year or later

    // Iterating over the year list
    while (list != NULL) {
        // Display only cars from the specified year or later
        if (list->year >= minYear) {
            YearCarNode* node = list->CarList;
            while (node != NULL) {
                Car* c = node->car;
                printf("| %-15s | %-15s | %-6d | %-10d | $%-12.2f |\n", c->brand, c->model, c->year, c->km, c->price);
                node = node->next;
                found = 1; // Car found
            }
        }
        list = list->next; // Move to the next year node
    }

    // If no car was found
    if (!found) {
        printf("No cars found from year %d or later.\n", minYear);
    }
    printf("---------------------------------------------------------------------------\n");
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
