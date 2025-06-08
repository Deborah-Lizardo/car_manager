#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/car.h"

int read_csv(Car* array, int max, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening CSV file");
        return 0;
    }

    int count = 0;
    char line[200];
    while (fgets(line, sizeof(line), file) && count < max) {
        Car c;
        scanf(line, "%[^;];%[^;];%d;%d;%f\n", c.brand, c.model, &c.year, &c.km, &c.price);
        array[count++] = c;
    }

    fclose(file);
    return count;
}

void save_binary(const char* filename, Car* array, int n) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Error creating binary file");
        return;
    }

    fwrite(&n, sizeof(int), 1, file);           // Write number of cars
    fwrite(array, sizeof(Car), n, file);        // Write car data
    fclose(file);
}

int load_binary(const char* filename, Car* array, int max) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening binary file");
        return 0;
    }

    int n;
    fread(&n, sizeof(int), 1, file);
    if (n > max) n = max;
    fread(array, sizeof(Car), n, file);
    fclose(file);
    return n;
}

void print_cars(Car* array, int n) {
    for (int i = 0; i < n; i++) {
        printf("Brand: %s | Model: %s | Year: %d | Km: %d | Price: %.2f\n",
               array[i].brand, array[i].model, array[i].year, array[i].km, array[i].price);
    }
}
