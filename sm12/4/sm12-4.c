#include "sys/wait.h"
#include <ctype.h>
#include <fcntl.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum { SIZE = 1000 };

int now = 0;

int main(int argc, char *argv[]) {

    int size = 0;
    int arr[SIZE];

    if (argc == 1) {
        return 0;
    }
    if (argc == 2) {
        int tmp = fork();
        if (tmp < 0) {
            return 1;
        } else if (tmp == 0) {
            execlp(argv[1], argv[1], (char *)NULL);
            _exit(1);
        } else {
            arr[size] = tmp;
            ++size;
        }
        wait(NULL);
        return 0;
    }

    int prev[2];
    if (pipe(prev) < 0) {
        for (int i = 0; i < size; ++i) {
            kill(arr[i], SIGKILL);
        }
        return 1;
    }
    int tmp = fork();
    if (tmp < 0) {
        return 1;
    } else if (tmp == 0) {
        dup2(prev[1], STDOUT_FILENO);
        close(prev[1]);
        close(prev[0]);
        execlp(argv[1], argv[1], (char *)NULL);
        _exit(1);
    } else {
        arr[size] = tmp;
        ++size;
    }
    close(prev[1]);

    for (int i = 2; i < argc - 1; ++i) {
        int now[2];
        if (pipe(now) < 0) {
            for (int j = 0; j < size; ++j) {
                kill(arr[j], SIGKILL);
            }
            return 1;
        }
        tmp = fork();
        if (tmp < 0) {
            for (int i = 0; i < size; ++i) {
                kill(arr[i], SIGKILL);
            }
            return 1;
        } else if (tmp == 0) {
            dup2(prev[0], STDIN_FILENO);
            dup2(now[1], STDOUT_FILENO);
            close(now[1]);
            close(prev[0]);
            close(now[0]);
            close(prev[1]);  // ?
            execlp(argv[i], argv[i], (char *)NULL);
            _exit(1);
        } else {
            arr[size] = tmp;
            ++size;
        }

        close(prev[0]);
        close(now[1]);

        prev[0] = now[0];
    }

    tmp = fork();
    if (tmp < 0) {
        for (int i = 0; i < size; ++i) {
            kill(arr[i], SIGKILL);
        }
        return 1;
    } else if (tmp == 0) {
        dup2(prev[0], STDIN_FILENO);
        close(prev[0]);
        close(prev[1]);  // ?
        execlp(argv[argc - 1], argv[argc - 1], (char *)NULL);
        _exit(1);
    } else {
        arr[size] = tmp;
        ++size;
    }

    close(prev[0]);
    for (int i = 1; i < argc; ++i) {
        wait(NULL);
    }
    return 0;
}