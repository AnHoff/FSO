#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <sys/shm.h>

int erro;

void executeCommand(const char* command, const char* argument);
void printExecutionTimeAndError(int erro, struct timeval inicio, struct timeval fim);
double calculateTimeDifference(struct timeval inicio, struct timeval fim);

int main(void) {
    char entrada1[255];
    char entrada2[255];
    pid_t pid = 1;
    struct timeval inicio, fim, inicio2, fim2;
    int shm_id;
    double soma = 0;
    int erro;

    gettimeofday(&inicio2, NULL);

    while (scanf("%s %s", entrada1, entrada2) != EOF) {
        fflush(stdout);
        pid = fork();
        gettimeofday(&inicio, NULL);

        if (pid == 0) {
            executeCommand(entrada1, entrada2);
        } else {
            waitpid(pid, &erro, WUNTRACED);
            erro = WEXITSTATUS(erro);
            
            gettimeofday(&fim, NULL);
            printExecutionTimeAndError(erro, inicio, fim);
        }
    }
    gettimeofday(&fim2, NULL);

    double periodo2 = calculateTimeDifference(inicio2, fim2);
    if (pid != 0) {
        printf(">> O tempo total foi de %0.1lf segundos\n", periodo2);
    }

    return 0;
}

void executeCommand(const char* command, const char* argument) {
    execl(command, command, argument, NULL);

    if (strerror(errno) != "Success") {
        printf("> Erro: %s\n", strerror(errno));
    }

    fflush(stdout);
    erro = errno;

    fclose(stdin);
    exit(errno);
}

void printExecutionTimeAndError(int erro, struct timeval inicio, struct timeval fim) {
    double periodo = calculateTimeDifference(inicio, fim);
    printf("> Demorou %0.1lf segundos, retornou %i\n", periodo, erro);
    fflush(stdout);
}

double calculateTimeDifference(struct timeval inicio, struct timeval fim) {
    return (fim.tv_sec - inicio.tv_sec) + 1e-6 * (fim.tv_usec - inicio.tv_usec);
}
