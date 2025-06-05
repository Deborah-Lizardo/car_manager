#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carro.h"
#include "lista.h"

#define MAX_LINHA 150

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Uso correto: %s <entrada.csv> <saida.bin>\n", argv[0]);
        return 1;
    }

    FILE* entrada = fopen(argv[1], "r");
    if (!entrada) {
        perror("Erro ao abrir o arquivo CSV");
        return 1;
    }

    No* lista = NULL;
    char linha[MAX_LINHA];
    int contador = 0;

    while (fgets(linha, MAX_LINHA, entrada)) {
        Carro c;
        if (sscanf(linha, "%[^,],%[^,],%d,%f,%f",
                   c.marca, c.modelo, &c.ano, &c.km, &c.preco) == 5) {
            lista = inserirFinal(lista, c);
            contador++;
                   }
    }

    fclose(entrada);

    FILE* saida = fopen(argv[2], "wb");
    if (!saida) {
        perror("Erro ao abrir o arquivo binário");
        liberarLista(lista);
        return 1;
    }

    fwrite(&contador, sizeof(int), 1, saida);

    No* atual = lista;
    while (atual != NULL) {
        fwrite(&(atual->carro), sizeof(Carro), 1, saida);
        atual = atual->prox;
    }

    fclose(saida);
    liberarLista(lista);

    printf("Dados salvos com sucesso em %s\n", argv[2]);
    return 0;
}
