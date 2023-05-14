#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum { LENGTH = 4096 };

void sayhi(int signo) {

    //    sigset_t sigint, oldmask;
    //
    //    sigemptyset(&sigint);
    //    sigaddset(&sigint, SIGTERM);
    //    sigprocmask(SIG_BLOCK, &sigint, &oldmask);
    //
    //    struct sigaction sa = {
    //        .sa_handler = sayhi,
    //        .sa_flags = SA_RESTART,
    //    };
    //    sigaction(SIGTERM, &sa, NULL);

    char *s = "We communicate on my terms.\n";
    if (write(STDOUT_FILENO, s, strlen(s))) {
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
    int tmp;
    while ((tmp = read(STDIN_FILENO, str, LENGTH)) > 0) {
        str[tmp] = '\0';
        if (write(STDOUT_FILENO, str, tmp)) {
            //
        }
        fflush(stdout);
    }
}
