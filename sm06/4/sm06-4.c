#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

enum { BUFF_SIZE = 10, NO_CATCHED_ERROR = 13 };

int stack[BUFF_SIZE];
jmp_buf jmpbuf[BUFF_SIZE];
int size = 0;

jmp_buf *try(int exception) {
    stack[size] = exception;
    ++size;
    return &jmpbuf[size - 1];
}

void endtry() {
    stack[size] = 0;
    --size;
}

void throw(int exception) {
    while (size > 0 && stack[size - 1] != exception) {
        --size;
    }
    if (size != 0) {
        --size;
        longjmp(jmpbuf[size], 1);
    } else {
        exit(NO_CATCHED_ERROR);
    }
}
