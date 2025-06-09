#ifndef LIST_H
#define LIST_H
#include "car.h"

typedef struct Node {
    Car car;
    struct Node* next;
} Node;

Node* insertAtEnd(Node* list, Car car);  // Inserts a car at the end of the list
void printList(Node* list);               // Prints all cars in the list
void freeList(Node* list);                // Frees all memory of the list

#endif
