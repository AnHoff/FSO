#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

pid_t zombie_pid = -1;
int signal_count = 0;

void signal_handler(int signum) {
    if (zombie_pid == -1) {
        zombie_pid = fork();
        if (zombie_pid == 0) {  // processo filho, não faz nada
            while (1) {
                pause();
            }
        }
    } else {
        kill(zombie_pid, SIGTERM);
        zombie_pid = -1;
        signal_count++;
    }

    if (signal_count >= 3) {
        if (zombie_pid != -1) {
            kill(zombie_pid, SIGTERM);
        }
        exit(0);
    }
}

int main() {
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    while (1) {
        pause();
    }

    return 0;
}
