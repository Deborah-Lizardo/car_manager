// arvore.h
#ifndef ARVORE_H
#define ARVORE_H

#include "carro.h"

typedef struct NoArvore {
    float chave; // Pode ser quilometragem ou preço
    Carro* carro; // Ponteiro para o carro correspondente no vetor
    struct NoArvore* esquerda;
    struct NoArvore* direita;
} NoArvore;

// Funções básicas
NoArvore* inserirArvore(NoArvore* raiz, float chave, Carro* carro);
void buscarIntervalo(NoArvore* raiz, float min, float max);
void liberarArvore(NoArvore* raiz);

#endif
