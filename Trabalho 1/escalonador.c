#include <stdio.h>
#include <stdlib.h>

struct Processo {
    int ID;
    int tempoRestante;
};

void enfileirar(struct Processo *fila, int *tamanho, struct Processo processo, int capacidade) {
    if (*tamanho < capacidade) {
        fila[*tamanho] = processo;
        (*tamanho)++;
    }
}

struct Processo desenfileirar(struct Processo *fila, int *tamanho) {
    struct Processo processo_vazio = { -1, 0 };
    
    if (*tamanho > 0) {
        struct Processo processo = fila[0];
        (*tamanho)--;
        
        for (int i = 0; i < *tamanho; i++) {
            fila[i] = fila[i + 1];
        }
        
        return processo;
    } else {
        return processo_vazio;
    }
}

int calculaFatiaTempo(int p, int t) {
    return (p < t) ? p : t;
}

int main() {
    int numProcessos, tempo;

    scanf("%d", &numProcessos);
    scanf("%d", &tempo);

    struct Processo *filaProntos = (struct Processo *)malloc(numProcessos * sizeof(struct Processo));
    int tamanhoFila = 0;

    for (int i = 0; i < numProcessos; i++) {
        struct Processo processo;
        scanf("%d", &processo.ID);

        int tempoExecucao;
        scanf("%d", &tempoExecucao);

        processo.tempoRestante = tempoExecucao * 1000;
        enfileirar(filaProntos, &tamanhoFila, processo, numProcessos);
    }

    int tempoAtual = 0;

    while (tamanhoFila > 0) {
        struct Processo processo = desenfileirar(filaProntos, &tamanhoFila);
        int fatiaTempo = calculaFatiaTempo(processo.tempoRestante, tempo);
        tempoAtual += fatiaTempo;
        processo.tempoRestante -= fatiaTempo;

        if (processo.tempoRestante > 0) {
            enfileirar(filaProntos, &tamanhoFila, processo, numProcessos);
        } else {
            printf("%d (%d)\n", processo.ID, tempoAtual);
        }
    }

    free(filaProntos);
    return 0;
}
