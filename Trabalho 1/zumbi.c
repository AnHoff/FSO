#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int executionCount = 0;

void signalHandler(int signalNumber);
void executeProcess();

int main() {
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);

    while (1) {
    }

    return 0;
}

void signalHandler(int signalNumber) {
    if (signalNumber == SIGUSR1) {
        switch (executionCount) {
            case 2:
                exit(0);
                break;
            case 1:
                executionCount++;
                wait(NULL);
                break;
            case 0:
                executionCount++;
                executeProcess();
                break;
        }
    }
    if (signalNumber == SIGUSR2) {
        switch (executionCount) {
            case 2:
                exit(0);
                break;
            case 1:
                executionCount++;
                wait(NULL);
                break;
            case 0:
                executionCount++;
                executeProcess();
                break;
        }
    }
}

void executeProcess() {
    if (fork() == 0) {
        exit(0);
    }
}