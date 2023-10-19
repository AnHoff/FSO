#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>

void execute_command(const char *path, const char *argument, double *total_time) {
    struct timeval start, end;
    double elapsed_time;

    gettimeofday(&start, NULL);

    pid_t pid = fork();

    if (pid == -1) {
        perror("Erro ao criar um processo filho");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        execl(path, path, argument, (char *)NULL);
        perror("Erro ao executar o comando");
        exit(EXIT_FAILURE);
    } else {
        int status;
        waitpid(pid, &status, 0);

        gettimeofday(&end, NULL);
        elapsed_time = (double)(end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;

        if (WIFEXITED(status)) {
            printf("> Demorou %.1f segundos, retornou %d\n", elapsed_time, WEXITSTATUS(status));
        } else {
            printf("> Erro: %s\n", strerror(errno));
        }

        *total_time += elapsed_time;
    }
}

int main() {
    char line[512];
    char path[256];
    char argument[256];
    double total_time = 0.0;

    while (fgets(line, sizeof(line), stdin)) {
        if (sscanf(line, "%s %s", path, argument) != 2) {
            fprintf(stderr, "Erro na entrada: Formato inválido\n");
            continue;
        }

        execute_command(path, argument, &total_time);
    }

    printf(">> O tempo total foi de %.1f segundos\n", total_time);

    return 0;
}
