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

    FILE *f_in = fopen(argv[1], "r");
    FILE *s_in = fopen(argv[2], "r");
    int fd_first[2];
    int fd_second[2];
    if (pipe(fd_first) < 0) {
        perror("pipe\n");
    }
    if (pipe(fd_second) < 0) {
        perror("pipe\n");
    }

    if (!fork()) {
        int sum = 0;
        int buf;
        while (fscanf(f_in, "%d", &buf) != EOF) {
            sum += buf;
        }
        if (write(fd_first[1], &sum, sizeof(int)) < 0) {
            return 1;
        }
        return 0;
    }

    if (!fork()) {
        int sum = 0;
        int buf;
        while (fscanf(s_in, "%d", &buf) != EOF) {
            sum += buf;
        }
        if (write(fd_second[1], &sum, sizeof(int)) < 0) {
            return 1;
        }
        return 0;
    }
    wait(NULL);
    wait(NULL);
    int f, s;
    if (read(fd_first[0], &f, 4) <= 0) {
        return 0;
    }
    if (read(fd_second[0], &s, 4) <= 0) {
        return 0;
    }
    printf("%d\n%d\n%d\n", s, f, f + s);
    return 0;
}