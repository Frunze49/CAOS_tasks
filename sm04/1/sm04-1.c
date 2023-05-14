#include <stdio.h>

int main(void) {
    unsigned int a, b, result, rem = 0;
    if (scanf("%u", &a) == 0 || scanf("%u", &b) == 0) {
        return 1;
    }
    if (a % 2 == 1 && b % 2 == 1) {
        rem = 1;
    }
    result = a / 2 + b / 2 + rem;
    printf("%u\n", result);
    return 0;
}
