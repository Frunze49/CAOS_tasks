#include <stdbool.h>

void normalize_path(char *buf) {
    char *tmp = buf;
    bool flag = false;
    while (*tmp != '\0') {
        if (*tmp == '/') {
            if (flag) {
                ++tmp;
            } else {
                flag = true;
                *buf = *tmp;
                ++tmp;
                ++buf;
            }
        } else {
            flag = false;
            *buf = *tmp;
            ++tmp;
            ++buf;
        }
    }
    *buf = *tmp;
}
