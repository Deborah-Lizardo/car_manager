#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/car.h"
#include "../include/year_list.h"
#include "../include/mil_tree.h"
#include "../include/price_tree.h"
#include <ctype.h>
// Function to display all cars
void displayAllCars(Car* cars, int count) {
    printf("\nDisplaying all cars:\n");
    printf("-------------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-6s | %-10s | %-12s |\n", "Brand", "Model", "Year", "Mileage", "Price");
    printf("-------------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("| %-15s | %-15s | %-6d | %-10d | $%-12.2f |\n", cars[i].brand, cars[i].model, cars[i].year, cars[i].km, cars[i].price);
    }
    printf("--------------------------------------------------------------------------\n");
}

// Function to convert a string to lowercase
void toLower(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Function to display cars filtered by model (case-insensitive) and sorted by price
void displayCarsByModel(Car* cars, int count, const char* substring) {
    int* indices = malloc(count * sizeof(int));
    if (indices == NULL) {
        printf("Memory allocation error\n");
        return;
    }

    int matchCount = 0;
    char lowerSubstring[100];
    strcpy(lowerSubstring, substring);
    toLower(lowerSubstring);

    // Filter the cars that contain the substring in the model (case-insensitive)
    for (int i = 0; i < count; i++) {
        // Copy the car model and convert it to lowercase
        char lowerModel[100];
        strcpy(lowerModel, cars[i].model);
        toLower(lowerModel);

        // Check if the model contains the substring (case-insensitive)
        if (strstr(lowerModel, lowerSubstring) != NULL) {
            indices[matchCount++] = i;
        }
    }

    // Check if no cars matched
    if (matchCount == 0) {
        printf("No cars found with the model containing the substring \"%s\"\n", substring);
        free(indices);  // Free memory before returning
        return;
    }

    // Sort the matching cars by price (non-decreasing order)
    for (int i = 0; i < matchCount - 1; i++) {
        for (int j = 0; j < matchCount - i - 1; j++) {
            if (cars[indices[j]].price > cars[indices[j + 1]].price) {
                int tmp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tmp;
            }
        }
    }

    // Display the filtered and sorted cars
    printf("| %-10s | %-10s | %-4s | %-8s | %-8s |\n", "Brand", "Model", "Year", "Km", "Price");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < matchCount; i++) {
        int idx = indices[i];
        printf("| %-10s | %-10s | %-4d | %-8d | R$%-7.2f |\n",
            cars[idx].brand, cars[idx].model, cars[idx].year, cars[idx].km, cars[idx].price);
    }

    printf("-------------------------------------------------------------\n");
    free(indices);
}

// Main function
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <binary_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (!file) {
        perror("Error opening binary file");
        return 1;
    }

    int count;
    fread(&count, sizeof(int), 1, file);
    Car* cars = malloc(count * sizeof(Car));
    fread(cars, sizeof(Car), count, file);
    fclose(file);

    // Data structures for trees
    YearNode* yearList = NULL;
    MileageTree* kmTree = NULL;
    PriceTree* priceTree = NULL;

    // Populate trees with car data
    for (int i = 0; i < count; i++) {
        yearList = insertYear(yearList, cars[i].year, &cars[i]);
        kmTree = insertNodeKm(kmTree, cars[i].km, &cars[i]);
        priceTree = insertPriceNode(priceTree, cars[i].price, &cars[i]);
    }

    // Interactive menu
    int option;
    do {
        printf("\nMenu:\n");
        printf("1. Display all cars\n");
        printf("2. Display cars by model (sorted by price)\n");
        printf("3. Display cars from a certain year\n");
        printf("4. Display cars by mileage range\n");
        printf("5. Display cars by price range\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        getchar();  // Consume '\n' after integer input

        if (option == 1) {
            displayAllCars(cars, count);

        } else if (option == 2) {
            char substring[50];
            printf("Enter part of the model name: ");
            fgets(substring, sizeof(substring), stdin);
            substring[strcspn(substring, "\n")] = '\0';  // Remove trailing newline
            displayCarsByModel(cars, count, substring);

        } else if (option == 3) {
            int minYear;
            printf("Enter minimum year: ");
            scanf("%d", &minYear);
            displayCarsFromYear(yearList, minYear);

        } else if (option == 4) {
            int minKm, maxKm;
            printf("Enter minimum mileage: ");
            scanf("%d", &minKm);
            printf("Enter maximum mileage: ");
            scanf("%d", &maxKm);
            searchMileage(kmTree, minKm, maxKm);  // Calls the mileage search

        } else if (option == 5) {
            float minPrice, maxPrice;
            printf("Enter minimum price: ");
            scanf("%f", &minPrice);
            printf("Enter maximum price: ");
            scanf("%f", &maxPrice);
            searchPrice(priceTree, minPrice, maxPrice);  // Calls the price search

        } else if (option == 6) {
            printf("Exiting program...\n");

        } else {
            printf("Invalid option.\n");
        }

    } while (option != 6);

    // Freeing memory
    free(cars);
    freeYearList(yearList);
    freeKmTree(kmTree);
    freePriceTree(priceTree);

    return 0;
}
