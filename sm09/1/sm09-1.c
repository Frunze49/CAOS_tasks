#include "stdio.h"
#include <stddef.h>

enum {
    FULL_ACCESS = 4095,
    TEN = 10,
    NINE = 9,
    SEVEN = 7,
    EIGHT = 8,
    ELEVEN = 11,
    FIVE = 5
};

const char *perms_to_str(char *buf, size_t size, int perms) {
    if (size == 0) {
        return buf;
    } else {
        int full_access = FULL_ACCESS;
        perms &= full_access;
    }
    char tmp_buf[TEN];
    int i = 0;
    while (i + 1 < TEN) {
        if (perms & (1 << (TEN - i - 2))) {
            if (i % 3 == 0) {
                tmp_buf[i] = 'r';
            } else if (i % 3 == 1) {
                tmp_buf[i] = 'w';
            } else if (i % 3 == 2) {
                tmp_buf[i] = 'x';
            }

        } else {
            tmp_buf[i] = '-';
        }
        ++i;
    }
    if (perms & (1 << NINE) && tmp_buf[EIGHT] != '-' && tmp_buf[SEVEN] != '-') {
        tmp_buf[EIGHT] = 't';
    }
    if (perms & (1 << TEN) && tmp_buf[EIGHT] != '-') {
        tmp_buf[FIVE] = 's';
    }
    if (perms & (1 << ELEVEN) &&
        (tmp_buf[FIVE] != '-' || tmp_buf[EIGHT] != '-')) {
        tmp_buf[2] = 's';
    }

    tmp_buf[i] = '\0';
    snprintf(buf, size, "%s", tmp_buf);
    return buf;
}