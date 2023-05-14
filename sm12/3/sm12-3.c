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

    int fd_first[2];
    int fd_second[2];
    if (pipe(fd_first) < 0) {
        perror("pipe\n");
    }
    if (pipe(fd_first) < 0) {
        perror("pipe\n");
    }
    if (pipe(fd_second) < 0) {
        perror("pipe\n");
    }
    int final = atoi(argv[1]);

    if (final < 2) {
        printf("Done\n");
        fflush(STDIN_FILENO);
        return 0;
    }

    FILE *fp_first_write = fdopen(fd_first[1], "w");
    FILE *fp_first_read = fdopen(fd_first[0], "r");
    FILE *fp_second_write = fdopen(fd_second[1], "w");
    FILE *fp_second_read = fdopen(fd_second[0], "r");

    fprintf(fp_second_write, "%d\n", 0);
    fflush(fp_second_write);

    if (!fork()) {
        int now;
        while (1) {
            if (fscanf(fp_second_read, "%d", &now) == 0) {
                continue;
            }
            printf("%d %d\n", 1, now + 1);
            fflush(STDIN_FILENO);

            ++now;
            fprintf(fp_first_write, "%d\n", now);
            fflush(fp_first_write);
            if (now + 2 >= final) {
                return 0;
            }
        }
    }
    if (!fork()) {
        int now;
        while (1) {
            if (final == 2) {
                return 0;
            }
            if (fscanf(fp_first_read, "%d", &now) == 0) {
                continue;
            }
            printf("%d %d\n", 2, now + 1);
            fflush(STDIN_FILENO);

            ++now;
            fprintf(fp_second_write, "%d\n", now);
            fflush(fp_second_write);
            if (now + 2 >= final) {
                return 0;
            }
        }
    }

    wait(NULL);
    wait(NULL);
    printf("Done\n");
    fflush(STDIN_FILENO);
    return 0;
}