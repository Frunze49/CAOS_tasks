#include "sys/wait.h"
#include <ctype.h>
#include <fcntl.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe\n");
    }
    if (!fork()) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);
        execlp(argv[1], argv[1], (char *)NULL);
        exit(1);
    }
    close(fd[1]);

    if (!fork()) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        execlp(argv[2], argv[2], (char *)NULL);
        exit(1);
    }

    close(fd[0]);
    wait(NULL);
    wait(NULL);
    return 0;
}