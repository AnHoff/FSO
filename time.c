#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main() {
    char cmd[256], arg[256];
    double total_time = 0;

    while (scanf("%s %s", cmd, arg) == 2) {
        struct timeval start_time, end_time;
        gettimeofday(&start_time, NULL);

        pid_t child_pid = fork();
        if (child_pid == -1) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        }
        if (child_pid == 0) {
            execlp(cmd, cmd, arg, NULL);
            perror("Error");
            exit(EXIT_FAILURE);
        } else {
            int status;
            waitpid(child_pid, &status, 0);
            gettimeofday(&end_time, NULL);
            double elapsed_time = (double)(end_time.tv_sec - start_time.tv_sec) +
                (double)(end_time.tv_usec - start_time.tv_usec) / 1000000;
            total_time += elapsed_time;
            if (WIFEXITED(status)) {
                printf("> Demorou %.1f segundos, retornou %d\n", elapsed_time, WEXITSTATUS(status));
            } else {
                printf("> Erro: %s\n", strerror(errno));
            }
        }
    }

    printf(">> O tempo total foi de %.1f segundos\n", total_time);

    return 0;
}
