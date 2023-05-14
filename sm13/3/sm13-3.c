#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t flag = 1;
volatile sig_atomic_t usr1 = 0;
volatile sig_atomic_t usr2 = 0;

void sayhi(int signo) {
    if (signo == SIGUSR1) {
        printf("%d\n%d\n", usr1, usr2);
        fflush(stdout);
        ++usr1;
    } else if (signo == SIGUSR2) {
        ++usr2;
    } else {
        flag = 0;
    }
}

int main() {
    sigset_t sigint, oldmask;

    sigemptyset(&sigint);
    sigaddset(&sigint, SIGUSR1);
    sigaddset(&sigint, SIGUSR2);
    sigaddset(&sigint, SIGTERM);
    sigprocmask(SIG_BLOCK, &sigint, &oldmask);

    struct sigaction sa = {
        .sa_handler = sayhi,
        .sa_flags = SA_RESTART,
    };
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    pid_t now = getpid();
    printf("%d\n", now);
    fflush(stdout);

    while (flag) {
        sigemptyset(&oldmask);
        sigsuspend(&oldmask);
    }
    exit(0);
}
