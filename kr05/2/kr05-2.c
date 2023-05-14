#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

enum { LENGTH = 8192 };

void sayhi(int signo) {

    sigset_t sigint, oldmask;

    sigemptyset(&sigint);
    sigaddset(&sigint, SIGTERM);
    sigprocmask(SIG_BLOCK, &sigint, &oldmask);

    struct sigaction sa = {
        .sa_handler = sayhi,
        .sa_flags = SA_RESTART,
    };
    sigaction(SIGTERM, &sa, NULL);

    char *s = "We communicate on my terms.\n";
    if(write(STDOUT_FILENO, s, strlen(s))) {
        (void)signo;
    }
}

int main() {
    sigset_t sigint, oldmask;

    sigemptyset(&sigint);
    sigaddset(&sigint, SIGTERM);
    sigprocmask(SIG_BLOCK, &sigint, &oldmask);

    struct sigaction sa = {
        .sa_handler = sayhi,
        .sa_flags = SA_RESTART,
    };
    sigaction(SIGTERM, &sa, NULL);
    sigprocmask(SIG_UNBLOCK, &sigint, &oldmask);
    char str[LENGTH];
    for (int i = 0; i < LENGTH; ++i) {
        str[i] = '\0';
    }
    while (1) {
        if (read(STDIN_FILENO, str, LENGTH) != 0) {
            if(write(STDOUT_FILENO, str, strlen(str))) {
                //
            }
            fflush(stdout);
            for (int i = 0; i < LENGTH; ++i) {
                str[i] = '\0';
            }
        }
    }
}
