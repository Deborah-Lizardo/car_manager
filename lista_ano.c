#include <stdio.h>
#include <stdlib.h>
#include "lista_ano.h"

NoAno* inserir_ano(NoAno* lista, int ano, Carro* carro) {
    NoAno* atual = lista;
    NoAno* anterior = NULL;

    while (atual != NULL && atual->ano < ano) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual != NULL && atual->ano == ano) {
        NoCarroAno* novoCarro = malloc(sizeof(NoCarroAno));
        novoCarro->carro = carro;
        novoCarro->prox = atual->listaCarros;
        atual->listaCarros = novoCarro;
        return lista;
    }

    NoAno* novoAno = malloc(sizeof(NoAno));
    novoAno->ano = ano;
    novoAno->listaCarros = NULL;
    novoAno->prox = atual;

    NoCarroAno* novoCarro = malloc(sizeof(NoCarroAno));
    novoCarro->carro = carro;
    novoCarro->prox = NULL;
    novoAno->listaCarros = novoCarro;

    if (anterior == NULL) {
        return novoAno;
    } else {
        anterior->prox = novoAno;
        return lista;
    }
}

void exibir_carros_por_ano(NoAno* lista, int ano_minimo) {
    while (lista != NULL) {
        if (lista->ano >= ano_minimo) {
            NoCarroAno* no = lista->listaCarros;
            while (no != NULL) {
                Carro* c = no->carro;
                printf("Marca: %s | Modelo: %s | Ano: %d | Km: %d | Preço: %.2f\n",
                       c->marca, c->modelo, c->ano, c->km, c->preco);
                no = no->prox;
            }
        }
        lista = lista->prox;
    }
}

void liberar_lista_ano(NoAno* lista) {
    while (lista != NULL) {
        NoAno* temp = lista;
        lista = lista->prox;

        NoCarroAno* no = temp->listaCarros;
        while (no != NULL) {
            NoCarroAno* aux = no;
            no = no->prox;
            free(aux);
        }

        free(temp);
    }
}
