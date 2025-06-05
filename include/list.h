#ifndef LIST_H
#define LIST_H

#include "car.h"

typedef struct Node {
    Car car;
    struct Node* next;
} Node;

// Main list functions
Node* insertAtEnd(Node* list, Car car);
void printList(Node* list);
void freeList(Node* list);

#endif
