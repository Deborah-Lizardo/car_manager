#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

Node* insertAtEnd(Node* list, Car car) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        return list;
    }
    newNode->car = car;
    newNode->next = NULL;

    if (list == NULL) return newNode;

    Node* current = list;
    while (current->next != NULL)
        current = current->next;

    current->next = newNode;
    return list;
}

void printList(Node* list) {
    while (list != NULL) {
        printf("Brand: %s | Model: %s | Year: %d | Km: %d | Price: %.2f\n",
               list->car.brand, list->car.model, list->car.year,
               list->car.km, list->car.price);
        list = list->next;
    }
}

void freeList(Node* list) {
    while (list != NULL) {
        Node* temp = list;
        list = list->next;
        free(temp);
    }
}

