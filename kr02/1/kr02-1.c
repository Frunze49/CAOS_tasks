#include <ctype.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
                *buf = *tmp;
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
