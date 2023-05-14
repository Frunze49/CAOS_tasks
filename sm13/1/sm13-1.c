#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t counter = 0;

void sayhi(int signo) {
    if (counter < 4) {
        printf("%d\n", counter);
        fflush(stdout);
    } else {
        exit(0);
    }
    (void)signo;
    ++counter;
}

int main() {
    sigset_t sigint, oldmask;

    sigemptyset(&sigint);
    sigaddset(&sigint, SIGINT);
    sigprocmask(SIG_BLOCK, &sigint, &oldmask);

    struct sigaction sa = {
        .sa_handler = sayhi,
        .sa_flags = SA_RESTART,
    };
    sigaction(SIGINT, &sa, NULL);

    pid_t now = getpid();
    printf("%d\n", now);
    fflush(stdout);
    sigprocmask(SIG_UNBLOCK, &sigint, &oldmask);

    while (1) {
        pause();
    }
}
