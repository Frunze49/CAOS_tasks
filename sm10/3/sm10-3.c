#include <stdio.h>

enum { MAX_ALLOW_FLOAT = 16777215 };

unsigned int func(unsigned int a) {
    if (a == 0) {
        return 0;
    }
    while (a % 2 == 0) {
        a /= 2;
    }
    if (a <= MAX_ALLOW_FLOAT) {
        return 0;
    }
    return 1;
}

int main() {
    unsigned int x;
    while (scanf("%u", &x) == 1) {
        if (func(x) == 0) {
            printf("%u\n", 1);
        } else {
            printf("%u\n", 0);
        }
    }
    return 0;
}