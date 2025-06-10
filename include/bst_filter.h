#ifndef BST_FILTER_H
#define BST_FILTER_H

#include "bst_price.h"  // ou onde Node está declarado

void filterByPrice(Node* root, int minPrice, int maxPrice);
void filterByMileage(Node* root, int minMileage, int maxMileage);

#endif
