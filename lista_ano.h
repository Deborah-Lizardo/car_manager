#ifndef LISTA_ANO_H
#define LISTA_ANO_H

#include "carro.h"

typedef struct NoCarroAno {
    Carro* carro; // ponteiro para o carro do vetor
    struct NoCarroAno* prox;
} NoCarroAno;

typedef struct NoAno {
    int ano;
    NoCarroAno* listaCarros; // lista de carros deste ano
    struct NoAno* prox;
} NoAno;

NoAno* inserir_ano(NoAno* lista, int ano, Carro* carro);
void exibir_carros_por_ano(NoAno* lista, int ano_minimo);
void liberar_lista_ano(NoAno* lista);

#endif
