#include "sys/wait.h"
#include <ctype.h>
#include <fcntl.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum { SIGN = 1024 };

void strip_spaces(char *buf) {

    char *tmp = buf;
    char *prev = buf;
    bool flag = false;
    int index = 0;
    while (*tmp != '\0') {
        if (isspace(*tmp)) {
            if (index == 0) {
                flag = true;
                ++tmp;
            } else if (flag) {
                ++tmp;
            } else {
                flag = true;
                *buf = ' ';
                prev = buf;
                ++tmp;
                ++buf;
                ++index;
            }
        } else {
            flag = false;
            *buf = *tmp;
            prev = buf;
            ++tmp;
            ++buf;
            ++index;
        }
    }
    if (isspace(*prev)) {
        *prev = *tmp;
    } else {
        *buf = *tmp;
    }
}

int mysystem(const char *cmd) {
    int tmp = snprintf(NULL, 0, "%s", cmd);
    char *buf = calloc(tmp + 1, sizeof(char));
    snprintf(buf, tmp + 1, "%s", cmd);
    strip_spaces(buf);
    char *old = buf;
    if (*buf == '\0') {
        return -1;
    }
    int size = 2;
    char *new_buf = buf;
    while (*new_buf != '\0') {
        if (*new_buf == ' ') {
            ++size;
        }
        ++new_buf;
    }
    char **argv = calloc(size, sizeof(char *));

    int now_size = 0;
    while (*(buf + now_size) != ' ' && *(buf + now_size) != '\0') {
        ++now_size;
    }
    argv[0] = calloc(now_size + 1, sizeof(char));
    snprintf(argv[0], now_size + 1, "%s", buf);
    int index = 1;
    if (size > 2) {
        buf += now_size + 1;
        now_size = 0;
        while (*(buf + now_size) != '\0') {
            if (*(buf + now_size) == ' ') {
                argv[index] = calloc(now_size + 1, sizeof(char));
                snprintf(argv[index], now_size + 1, "%s", buf);
                ++index;
                ++now_size;
                buf += now_size;
                now_size = 0;
            } else {
                ++now_size;
            }
        }
        argv[index] = calloc(now_size + 1, sizeof(char));
        snprintf(argv[index], now_size + 1, "%s", buf);
        ++index;
    }

    argv[index] = NULL;
    int res = fork();
    if (res < 0) {
        return -1;
    } else if (res == 0) {
        execvp(argv[0], argv);
        _exit(1);
    } else {
        int status;
        waitpid(res, &status, 0);
        for (int i = 0; i < index; ++i) {
            free(argv[i]);
        }
        free(argv);
        free(old);
        if (WIFSIGNALED(status)) {
            return WTERMSIG(status) + SIGN;
        } else {
            return WEXITSTATUS(status);
        }
    }
}
