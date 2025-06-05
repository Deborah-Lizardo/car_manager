#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/car.h"

int ler_csv(Carro* vetor, int max, const char* nomeArquivo) {
    FILE* arq = fopen(nomeArquivo, "r");
    if (!arq) {
        perror("Erro ao abrir o arquivo CSV");
        return 0;
    }

    int count = 0;
    char linha[200];
    while (fgets(linha, sizeof(linha), arq) && count < max) {
        Carro c;
        sscanf(linha, "%[^;];%[^;];%d;%d;%f\n", c.marca, c.modelo, &c.ano, &c.km, &c.preco);
        vetor[count++] = c;
    }

    fclose(arq);
    return count;
}

void salvar_binario(const char* nomeArquivo, Carro* vetor, int n) {
    FILE* arq = fopen(nomeArquivo, "wb");
    if (!arq) {
        perror("Erro ao criar o arquivo binário");
        return;
    }

    fwrite(&n, sizeof(int), 1, arq); // salva quantidade
    fwrite(vetor, sizeof(Carro), n, arq);
    fclose(arq);
}

int carregar_binario(const char* nomeArquivo, Carro* vetor, int max) {
    FILE* arq = fopen(nomeArquivo, "rb");
    if (!arq) {
        perror("Erro ao abrir o arquivo binário");
        return 0;
    }

    int n;
    fread(&n, sizeof(int), 1, arq);
    if (n > max) n = max;
    fread(vetor, sizeof(Carro), n, arq);
    fclose(arq);
    return n;
}

void imprimir_carros(Carro* vetor, int n) {
    for (int i = 0; i < n; i++) {
        printf("Marca: %s | Modelo: %s | Ano: %d | Km: %d | Preço: %.2f\n",
               vetor[i].marca, vetor[i].modelo, vetor[i].ano, vetor[i].km, vetor[i].preco);
    }
}
