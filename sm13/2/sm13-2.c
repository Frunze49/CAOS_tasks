#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t usr1 = 0;
volatile sig_atomic_t usr2 = 0;

void sayhi(int signo) {
    if (signo == SIGUSR1) {
        printf("%d %d\n", usr1, usr2);
        fflush(stdout);
        ++usr1;
    } else if (signo == SIGUSR2) {
        ++usr2;
    } else {

    }
}

int main() {
    sigset_t sigint;

    sigemptyset(&sigint);
    sigaddset(&sigint, SIGUSR1);
    sigaddset(&sigint, SIGUSR2);
    sigaddset(&sigint, SIGTERM);

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

    while (scanf("%d", &value) != EOF) {
        if (mode == 1) {
            long long val = (long long)value;
            printf("%lld\n", -val);
            fflush(stdout);
        } else {
            long long val = (long long)value;
            printf("%lld\n", val * val);
            fflush(stdout);
        }
    }
}
