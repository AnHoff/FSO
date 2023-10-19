#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int signal_count = 0;
pid_t zombie_pid = -1;

void signal_handler(int signum) {
    signal_count++;

    if (signal_count == 1) {
        zombie_pid = fork();
        if (zombie_pid == 0) {
            while (1) {
                sleep(1);
            }
        }
    } else if (signal_count == 2) {
        if (zombie_pid > 0) {
            kill(zombie_pid, SIGTERM);
            waitpid(zombie_pid, NULL, 0);
        }
    } else if (signal_count == 3) {
        if (zombie_pid > 0) {
            kill(zombie_pid, SIGTERM);
            waitpid(zombie_pid, NULL, 0);
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
