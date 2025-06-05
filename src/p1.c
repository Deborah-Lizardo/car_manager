#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/car.h"
#include "../include/list.h"

#define MAX_LINE 150

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input.csv> <output.bin>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening CSV file");
        return 1;
    }

    Node* list = NULL;
    char line[MAX_LINE];
    int count = 0;

    while (fgets(line, MAX_LINE, input)) {
        Car c;
        // Read brand, model, year, mileage, price from CSV line
        if (sscanf(line, "%[^,],%[^,],%d,%d,%f",
                   c.brand, c.model, &c.year, &c.mileage, &c.price) == 5) {
            list = insertAtEnd(list, c);
            count++;
                   }
    }

    fclose(input);

    FILE* output = fopen(argv[2], "wb");
    if (!output) {
        perror("Error opening binary file");
        freeList(list);
        return 1;
    }

    // Write number of records
    fwrite(&count, sizeof(int), 1, output);

    Node* current = list;
    while (current != NULL) {
        fwrite(&(current->car), sizeof(Car), 1, output);
        current = current->next;
    }

    fclose(output);
    freeList(list);

    printf("Data successfully saved to %s\n", argv[2]);
    return 0;
}
