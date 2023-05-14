#include "sys/wait.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signalfd.h>
#include <unistd.h>

pid_t first = 0, second = 0;

void sayhi(int signo) {
}

int main(int argc, char *argv[]) {

    sigset_t sigint, oldmask;

    sigemptyset(&sigint);
    sigaddset(&sigint, SIGUSR1);

    sigprocmask(SIG_BLOCK, &sigint, &oldmask);

    struct sigaction sa = {
        .sa_handler = sayhi,
        .sa_flags = SA_RESTART,
    };
    sigaction(SIGUSR1, &sa, NULL);
    sigprocmask(SIG_UNBLOCK, &sigint, &oldmask);

    int fd_first[2];
    if (pipe(fd_first) < 0) {
        perror("pipe\n");
    }
    int final = atoi(argv[1]);

    if (final < 1) {
        return 0;
    }

    FILE *fp_first_write = fdopen(fd_first[1], "w");
    FILE *fp_first_read = fdopen(fd_first[0], "r");

    pid_t tmp;
    if (!(tmp = fork())) {
        int now = 0;
        fflush(STDIN_FILENO);
        while (1) {
            if (fscanf(fp_first_read, "%d", &now) == 0) {
                continue;
            }
            if (second == 0) {
                second = now;
                now = 0;
            }
            printf("%d %d\n", 1, now + 1);
            fflush(STDIN_FILENO);

            ++now;
            fprintf(fp_first_write, "%d\n", now);
            fflush(fp_first_write);

            kill(second, SIGUSR1);
            if (now + 2 > final) {
                return 0;
            }
            pause();
        }
    }
    first = tmp;
    if (!(tmp = fork())) {
        if (final == 1) {
            return 0;
        }
        int now;
        while (1) {
            if (fscanf(fp_first_read, "%d", &now) == 0) {
                continue;
            }
            printf("%d %d\n", 2, now + 1);
            fflush(STDIN_FILENO);
            ++now;
            fprintf(fp_first_write, "%d\n", now);
            fflush(fp_first_write);
            kill(first, SIGUSR1);
            if (now + 2 > final) {
                return 0;
            }
            pause();
        }
    }
    fprintf(fp_first_write, "%d\n", tmp);
    fflush(fp_first_write);
    wait(NULL);
    wait(NULL);
    fflush(STDIN_FILENO);
    return 0;
}