#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/car.h"
#include "../include/list.h"
#include "../include/year_list.h"

#define MAX_LINE 150

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 3) {
        printf("Usage: %s <input.csv> <output.bin>\n", argv[0]);
        return 1;  // Exit if arguments are incorrect
    }

    // Open the input CSV file for reading
    FILE* input = fopen(argv[1], "r");
    if (!input) {
        perror("Error opening CSV file");
        return 1;  // Exit if the file cannot be opened
    }

    Node* list = NULL;  // Initialize an empty list for storing cars
    char line[MAX_LINE];  // Buffer to hold each line read from the CSV file
    int count = 0;  // Counter to track the number of cars read
    int isFirstLine = 1;  // Flag to skip the header line in the CSV file

    // Read the CSV file and populate the car list
    while (fgets(line, MAX_LINE, input)) {
        // Remove the newline character, if present, at the end of the line
        line[strcspn(line, "\n")] = '\0';

        // Skip the header line if it contains "brand" (indicating column names)
        if (isFirstLine && strstr(line, "brand") != NULL) {
            isFirstLine = 0;
            continue;  // Move to the next line
        }

        Car c;  // Variable to store car data
        // Parse each line into the car structure
        if (sscanf(line, "%[^,],%[^,],%d,%d,%f",
                   c.brand, c.model, &c.year, &c.km, &c.price) == 5) {
            list = insertAtEnd(list, c);  // Insert the car into the list
            count++;  // Increment the counter
        } else {
            // Print a message if the line format is invalid
            fprintf(stderr, "Skipped line (invalid format): %s\n", line);
        }
        isFirstLine = 0;  // Ensure header is skipped only once
    }

    fclose(input);  // Close the input CSV file

    // Open the output binary file for writing
    FILE* output = fopen(argv[2], "wb");
    if (!output) {
        perror("Error opening binary file");
        freeList(list);  // Free the allocated memory for the list before exiting
        return 1;  // Exit if the file cannot be opened
    }

    // Write the number of records (cars) to the binary file
    fwrite(&count, sizeof(int), 1, output);

    Node* current = list;  // Pointer to traverse the car list
    // Write each car's data to the binary file
    while (current != NULL) {
        fwrite(&(current->car), sizeof(Car), 1, output);
        current = current->next;  // Move to the next node in the list
    }

    fclose(output);  // Close the output binary file
    freeList(list);  // Free the memory allocated for the list

    // Print a success message with the number of records saved
    printf("Data successfully saved to %s (%d records)\n", argv[2], count);
    return 0;  // Exit the program successfully
}
