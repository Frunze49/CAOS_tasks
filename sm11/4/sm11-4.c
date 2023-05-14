#include "sys/wait.h"
#include <ctype.h>
#include <fcntl.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum { SIZE = 100000, NAME_SIZE = 300 };

int main(int argc, char *argv[]) {

    char name[NAME_SIZE];
    int offset = 0;
    if (getenv("XDG_RUNTIME_DIR")) {
        offset = snprintf(name, NAME_SIZE, "%s/", getenv("XDG_RUNTIME_DIR"));
    } else if (getenv("TMPDIR")) {
        offset = snprintf(name, NAME_SIZE, "%s/", getenv("TMPDIR"));
    } else {
        offset = snprintf(name, NAME_SIZE, "/tmp/");
    }

    snprintf(name + offset, NAME_SIZE, "%d", getpid());
    int fd = open(name, O_CREAT | O_WRONLY, 0700);

    char *arr = calloc(SIZE, sizeof(char));
    offset = snprintf(arr, SIZE, "%s", "args = [ ");
    for (int i = 1; i < argc; ++i) {
        if (i == argc - 1) {
            offset += snprintf(arr + offset, SIZE, "%s ", argv[i]);
        } else {
            offset += snprintf(arr + offset, SIZE, "%s, ", argv[i]);
        }
    }
    snprintf(arr + offset, SIZE, "%s", "]");
    char buf[SIZE];
    int side = snprintf(buf, SIZE,
                        "#!/usr/bin/python3\n"
                        "\n"
                        "import sys\n"
                        "from os import remove\n"
                        "from sys import argv\n"
                        "\n");
    side += snprintf(buf + side, SIZE, "%s\n", arr);
    side += snprintf(buf + side, SIZE,
                     "\n"
                     "sum = 1\n"
                     "for i in args:\n"
                     "  sum *= int(i)\n"
                     "print(sum)\n"
                     "remove(argv[0])\n");
    int res = write(fd, buf, side);
    if (res < 0) {
        perror("sad\n");
    }
    close(fd);

    free(arr);
    char *args[2];
    args[0] = name;
    args[1] = NULL;
    execl(args[0], args[0], (char *)NULL);
    return 0;
}