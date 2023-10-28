#include <stdio.h>
#include <stdlib.h>

#define MAXPROC 100
#define MAXPID 200

typedef struct {
    int pid;
    int tempo_restante;
} Processo;

Processo processos[MAXPROC];

int comp(const void *a, const void *b) {
    return ((Processo *)a)->tempo_restante - ((Processo *)b)->tempo_restante;
}

int main() {
    int numProcessos, tempo;

    scanf("%d", &numProcessos);
    scanf("%d", &tempo);

    for (int count = 0; count < numProcessos; count++) {
        scanf("%d %d", &processos[count].pid, &processos[count].tempo_restante);

        processos[count].tempo_restante = processos[count].tempo_restante * 1000;
    }

    int t = 0;

    while (numProcessos > 0) {

        for (int count = 0; count < numProcessos; count++) {

            int quantum;

            if (processos[count].tempo_restante < tempo) {
                quantum = processos[count].tempo_restante;
            } else {
                quantum = tempo;
            }

            processos[count].tempo_restante -= quantum;
            t += quantum;

            if (processos[count].tempo_restante <= 0) {

                printf("%d (%d)\n", processos[count].pid, t);

                for (int j = count; j < numProcessos - 1; j++) {
                    processos[j] = processos[j + 1];
                }

                numProcessos--;
                count--;
            }
            
        }
    }

    return 0;
}