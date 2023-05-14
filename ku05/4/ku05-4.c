#include "sys/wait.h"
#include <ctype.h>
#include <fcntl.h>
#include <math.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    //    printf("%.10g", cos(-3.14159265359) * cos(-3.14159265359));
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

    double init = strtod(argv[1], NULL), step = strtod(argv[3], NULL);
    int final = atoi(argv[2]);

    if (!fork()) {
        if (!fork()) {
            double now;
            double ans = 0;
            for (int i = 0; i < final + 1; ++i) {
                double tmp = sin(init + i * step);
                if (write(fd_first[1], &tmp, sizeof(double))) {
                    //
                }
            }

            for (int i = 0; i < final + 1; ++i) {
                if (read(fd_second[0], &now, sizeof(now)) > 0) {
                    //
                }
                ans += now * now;
            }

            printf("1 %.10g\n", ans);
            return 0;
        }
        wait(NULL);
        exit(0);
    }
    if (!fork()) {
        if (!fork()) {
            double now;
            double ans = 0;
            for (int i = 0; i < final + 1; ++i) {
                if (read(fd_first[0], &now, sizeof(double)) >= 0) {
                    //
                }
                ans += fabs(now);
            }
            for (int i = 0; i < final + 1; ++i) {
                double tmp = cos(init + i * step);
                if (write(fd_second[1], &tmp, sizeof(double))) {
                    //
                }
            }
            printf("2 %.10g\n", ans);
            return 0;
        }
        wait(NULL);
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    printf("0 0\n");
    fflush(STDIN_FILENO);
    return 0;
}