#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

// Insert a car at the end of the list
Node* insertAtEnd(Node* list, Car car) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation error.\n");
        return list;
    }
    newNode->car = car;
    newNode->next = NULL;

    if (list == NULL) {
        return newNode;
    }

    Node* current = list;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;

    return list;
}

// Print all cars in the list
void printList(Node* list) {
    Node* current = list;
    while (current != NULL) {
        printf("Brand: %s | Model: %s | Year: %d | Price: %.2f | Mileage: %d\n",
               current->car.brand,
               current->car.model,
               current->car.year,
               current->car.price,
               current->car.mileage);
        current = current->next;
    }
}

// Free all memory allocated for the list
void freeList(Node* list) {
    Node* current = list;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}
