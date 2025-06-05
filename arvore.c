// arvore.c
#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

NoArvore* inserirArvore(NoArvore* raiz, float chave, Carro* carro) {
    if (raiz == NULL) {
        NoArvore* novo = (NoArvore*) malloc(sizeof(NoArvore));
        novo->chave = chave;
        novo->carro = carro;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }

    if (chave < raiz->chave)
        raiz->esquerda = inserirArvore(raiz->esquerda, chave, carro);
    else
        raiz->direita = inserirArvore(raiz->direita, chave, carro);

    return raiz;
}

void buscarIntervalo(NoArvore* raiz, float min, float max) {
    if (raiz == NULL)
        return;

    if (raiz->chave >= min)
        buscarIntervalo(raiz->esquerda, min, max);

    if (raiz->chave >= min && raiz->chave <= max) {
        printf("Marca: %s | Modelo: %s | Ano: %d | KM: %.0f | Preço: %.2f\n",
               raiz->carro->marca, raiz->carro->modelo,
               raiz->carro->ano, raiz->carro->km, raiz->carro->preco);
    }

    if (raiz->chave <= max)
        buscarIntervalo(raiz->direita, min, max);
}

void liberarArvore(NoArvore* raiz) {
    if (raiz == NULL)
        return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}
