#ifndef LISTA_H
#define LISTA_H

#include "carro.h"

typedef struct No {
    Carro carro;
    struct No* prox;
} No;

// Funções principais da lista
No* inserirFinal(No* lista, Carro carro);
void imprimirLista(No* lista);
void liberarLista(No* lista);

#endif
