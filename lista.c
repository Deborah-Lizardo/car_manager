#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Insere um carro no final da lista
No* inserirFinal(No* lista, Carro carro) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocação de memória.\n");
        return lista;
    }
    novo->carro = carro;
    novo->prox = NULL;

    if (lista == NULL) {
        return novo;
    }

    No* atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = novo;

    return lista;
}

// Imprime todos os carros da lista
void imprimirLista(No* lista) {
    No* atual = lista;
    while (atual != NULL) {
        printf("Marca: %s | Modelo: %s | Ano: %d | Preço: %.2f | KM: %.0f\n",
               atual->carro.marca,
               atual->carro.modelo,
               atual->carro.ano,
               atual->carro.preco,
               atual->carro.km);
        atual = atual->prox;
    }
}

// Libera toda a memória da lista
void liberarLista(No* lista) {
    No* atual = lista;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
}
