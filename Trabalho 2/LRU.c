// Resultado: wrong answer

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *quadros;
    int *contagem;
    int tamanho;
} MemoriaRAM;

void inicializarMemoriaRAM(MemoriaRAM *memoria, int tamanho) {
    memoria->quadros = (int *)malloc(tamanho * sizeof(int));
    memoria->contagem = (int *)malloc(tamanho * sizeof(int));
    memoria->tamanho = tamanho;

    for (int i = 0; i < tamanho; i++) {
        memoria->quadros[i] = -1;
        memoria->contagem[i] = 0;
    }
}

int buscarNaMemoriaRAM(MemoriaRAM *memoria, int pagina) {
    for (int i = 0; i < memoria->tamanho; i++) {
        if (memoria->quadros[i] == pagina) {
            memoria->contagem[i] = 0;  // Página usada recentemente, resetando a contagem
            return 1;  // Página encontrada na memória
        }
    }
    return 0;  // Página não encontrada na memória
}

void adicionarNaMemoriaRAM(MemoriaRAM *memoria, int pagina) {
    int indiceMenosUsado = 0;
    for (int i = 1; i < memoria->tamanho; i++) {
        if (memoria->contagem[i] > memoria->contagem[indiceMenosUsado]) {
            indiceMenosUsado = i;
        }
    }

    memoria->quadros[indiceMenosUsado] = pagina;
    memoria->contagem[indiceMenosUsado] = 0;  // Página adicionada, resetando a contagem
}

void atualizarContagem(MemoriaRAM *memoria) {
    for (int i = 0; i < memoria->tamanho; i++) {
        memoria->contagem[i]++;
    }
}

int main() {
    int Q, N;
    scanf("%d", &Q);
    scanf("%d", &N);

    MemoriaRAM memoria;
    inicializarMemoriaRAM(&memoria, Q);

    int *referencias = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        scanf("%d", &referencias[i]);
    }

    int pageFaults = 0;

    for (int i = 0; i < N; i++) {
        int pagina = referencias[i];

        if (!buscarNaMemoriaRAM(&memoria, pagina)) {
            adicionarNaMemoriaRAM(&memoria, pagina);
            pageFaults++;
        }

        atualizarContagem(&memoria);
    }

    printf("%d\n", pageFaults);

    // Liberando a memória alocada
    free(memoria.quadros);
    free(memoria.contagem);
    free(referencias);

    return 0;
}
