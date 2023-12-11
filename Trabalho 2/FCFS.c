// Resultado: wrong answer

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int processo;
    int tempo_execucao;
} Resultado;

void escalonador_fcfs(int N, int *quantidade_instrucoes, int **instrucoes_processos, Resultado *resultados) {
    int tempo_atual = 0;

    for (int i = 0; i < N; i++) {
        int processo = i + 1;

        for (int j = 0; j < quantidade_instrucoes[i]; j++) {
            if (instrucoes_processos[i][j] == 0) {
                tempo_atual += 10;
            } else if (instrucoes_processos[i][j] == 1) {
                tempo_atual += 0;  // Tempo para transformar instrução blocante em não blocante
                instrucoes_processos[i][j] = 0;  // Transforma instrução blocante em não blocante
            }
        }

        resultados[i].processo = processo;
        resultados[i].tempo_execucao = tempo_atual;
    }
}

int comparar_resultados(const void *a, const void *b) {
    return ((Resultado *)a)->tempo_execucao - ((Resultado *)b)->tempo_execucao;
}

int main() {
    int N;
    scanf("%d", &N);

    int *quantidade_instrucoes = (int *)malloc(N * sizeof(int));
    int **instrucoes_processos = (int **)malloc(N * sizeof(int *));
    Resultado *resultados = (Resultado *)malloc(N * sizeof(Resultado));

    for (int i = 0; i < N; i++) {
        scanf("%d", &quantidade_instrucoes[i]);
        instrucoes_processos[i] = (int *)malloc(quantidade_instrucoes[i] * sizeof(int));

        for (int j = 0; j < quantidade_instrucoes[i]; j++) {
            scanf("%d", &instrucoes_processos[i][j]);
        }
    }

    escalonador_fcfs(N, quantidade_instrucoes, instrucoes_processos, resultados);

    // Ordena os resultados com base no tempo de execução
    qsort(resultados, N, sizeof(Resultado), comparar_resultados);

    // Imprime os resultados ordenados
    for (int i = 0; i < N; i++) {
        printf("%d (%d)\n", resultados[i].processo, resultados[i].tempo_execucao);
    }

    // Liberando a memória alocada
    for (int i = 0; i < N; i++) {
        free(instrucoes_processos[i]);
    }
    free(quantidade_instrucoes);
    free(instrucoes_processos);
    free(resultados);

    return 0;
}
