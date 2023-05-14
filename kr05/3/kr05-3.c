#include "sys/wait.h"
#include <ctype.h>
#include <fcntl.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if(!fork()) {

    }

    if (!fork()) {

    }

    wait(NULL);
    exit(0);

}