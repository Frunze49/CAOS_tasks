#include "sys/wait.h"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/signalfd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum { TWENTY = 20, SIXTEEN = 16 };

int num;
char **files;
long long sums[TWENTY];

struct Block {
    char text[SIXTEEN];
};

void sayhi(int signo) {
    if (signo == SIGTERM) {
        for (int i = 0; i < num; ++i) {
            printf("%lld\n", sums[i]);
            fflush(stdout);
        }
        exit(0);
    } else if (signo >= SIGRTMIN && signo <= SIGRTMIN + TWENTY) {

        sigset_t sigint, oldmask;
        sigemptyset(&sigint);
        sigaddset(&sigint, SIGTERM);
        for (int i = 0; i < TWENTY; ++i) {
            sigaddset(&sigint, SIGRTMIN + i);
        }
        sigprocmask(SIG_BLOCK, &sigint, &oldmask);
        struct sigaction sa = {
            .sa_handler = sayhi,
            .sa_flags = 0,
        };
        sigaction(SIGTERM, &sa, NULL);
        for (int i = 0; i < TWENTY; ++i) {
            sigaction(SIGRTMIN + i, &sa, NULL);
        }

        if (files[signo - SIGRTMIN + 1][0] == '\0') {
            return;
        }
        int fd = open(files[signo - SIGRTMIN + 1], O_RDONLY);
        struct Block b;

        sigprocmask(SIG_UNBLOCK, &sigint, &oldmask);
        int tmp;
        while ((tmp = read(fd, &b, sizeof(b))) > 0) {
            long long tmp;
            sscanf(b.text, "%lld", &tmp);
            sums[signo - SIGRTMIN] += tmp;
            fflush(stdout);
        }
        sigprocmask(SIG_BLOCK, &sigint, &oldmask);
        if (tmp != -1) {
            close(fd);
            files[signo - SIGRTMIN + 1][0] = '\0';
        }
    }
}

int main(int argc, char *argv[]) {
    num = argc - 1;
    files = argv;
    for (int i = 0; i < argc - 1; ++i) {
        sums[i] = 0;
    }

    sigset_t sigint, oldmask;

    sigemptyset(&sigint);
    sigaddset(&sigint, SIGTERM);
    for (int i = 0; i < TWENTY; ++i) {
        sigaddset(&sigint, SIGRTMIN + i);
    }
    sigprocmask(SIG_BLOCK, &sigint, &oldmask);

    struct sigaction sa = {
        .sa_handler = sayhi,
        .sa_flags = 0,
    };
    sigaction(SIGTERM, &sa, NULL);
    for (int i = 0; i < TWENTY; ++i) {
        sigaction(SIGRTMIN + i, &sa, NULL);
    }

    pid_t now = getpid();
    printf("%d\n", now);
    fflush(stdout);

    while (1) {
        sigemptyset(&oldmask);
        sigsuspend(&oldmask);
    }
}