#include "sys/types.h"
#include "sys/wait.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

int x = 0;
pid_t init = 0;

void reader() {
    int status = 0;
    if (scanf("%d", &x) == EOF) {

    } else {
        pid_t res = fork();
        if (res < 0) {
            printf("%d\n", -1);
            exit(1);
        } else if (res != 0) {
            wait(&status);
            if (WEXITSTATUS(status) != 0) {
                if (init == getpid()) {
                    exit(0);
                }
                exit(1);
            }
            printf("%d\n", x);
        } else {
            reader();
        }
    }
}

int main(void) {
    init = getpid();
    reader();
    return 0;
}