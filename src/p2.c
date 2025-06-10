#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/car.h"
#include "../include/year_list.h"
#include "../include/mil_tree.h"
#include "../include/price_tree.h"

void displayAllCars(Car* cars, int count) {
    for (int i = 0; i < count; i++) {
        printf("Brand: %s | Model: %s | Year: %d | Mileage: %d | Price: %.2f\n",
               cars[i].brand, cars[i].model, cars[i].year, cars[i].km, cars[i].price);
    }
}

void displayCarsByModel(Car* cars, int count, const char* substring) {
    // Displays cars whose model contains the substring, sorted by price
    int* indices = malloc(count * sizeof(int));
    int matchCount = 0;

    for (int i = 0; i < count; i++) {
        if (strstr(cars[i].model, substring) != NULL) {
            indices[matchCount++] = i;
        }
    }

    // Sort the matches by price (simple bubble sort)
    for (int i = 0; i < matchCount - 1; i++) {
        for (int j = 0; j < matchCount - i - 1; j++) {
            if (cars[indices[j]].price > cars[indices[j + 1]].price) {
                int tmp = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tmp;
            }
        }
    }

    if (matchCount == 0) {
        printf("No cars found with model containing \"%s\".\n", substring);
    } else {
        for (int i = 0; i < matchCount; i++) {
            int idx = indices[i];
            printf("Brand: %s | Model: %s | Year: %d | Mileage: %d | Price: %.2f\n",
                   cars[idx].brand, cars[idx].model, cars[idx].year, cars[idx].km, cars[idx].price);
        }
    }

    free(indices);
}

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

    // Data structures
    YearNode* yearList = NULL;
    MileageTree* kmTree = NULL;
    PriceTree* priceTree = NULL;

    for (int i = 0; i < count; i++) {
        yearList = insertYear(yearList, cars[i].year, &cars[i]);
        kmTree = insertNode(kmTree, cars[i].km, &cars[i]);
        priceTree = insertPriceNode(priceTree, cars[i].price, &cars[i]);
    }

    // INTERACTIVE MENU
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
        getchar();  // consume '\n'

        if (option == 1) {
            displayAllCars(cars, count);
        } else if (option == 2) {
            char substring[50];
            printf("Enter part of the model name: ");
            fgets(substring, sizeof(substring), stdin);
            substring[strcspn(substring, "\n")] = '\0';  // remove '\n'
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
            search(kmTree, minKm, maxKm);
        } else if (option == 5) {
            float minPrice, maxPrice;
            printf("Enter minimum price: ");
            scanf("%f", &minPrice);
            printf("Enter maximum price: ");
            scanf("%f", &maxPrice);
            searchPriceInterval(priceTree, minPrice, maxPrice);
        } else if (option == 6) {
            printf("Exiting program...\n");
        } else {
            printf("Invalid option.\n");
        }

    } while (option != 6);

    // Free memory 
    free(cars);
    freeYearList(yearList);
    freeTree(kmTree);
    freePriceTree(priceTree);

    return 0;
}
