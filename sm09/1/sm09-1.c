#include "stdio.h"

enum { FULL_ACCESS = 4095 };

const char *perms_to_str(char *buf, size_t size, int perms) {
    if (size == 0) {
        buf[0] = '\0';
        return buf;
    } else {
        int full_access = FULL_ACCESS;
        perms &= full_access;
    }
    char tmp_buf[10];
    int i = 0;
    while (i + 1 < 10) {
        if (perms & (1 << (10 - i - 2))) {
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

    tmp_buf[i] = '\0';
    snprintf(buf, size, "%s", tmp_buf);
    return buf;
}

int main() {
    char buf[16];
    for (int i = 0; i < 07777; ++i) {
        printf("%s\n", perms_to_str(buf, sizeof(buf), i));
    }
    return 0;
}