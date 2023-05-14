#include <stdio.h>
#include <stdlib.h>

enum { BASE = 13, INT_MIN = -2147483648 };

void please_compute_and_print_some_strange_values_from_some_other_strange_values(
    const char *val1, const char *val2) {
    int64_t first, second;
    int32_t res = 0;
    first = strtol(val1, NULL, BASE);
    second = strtol(val2, NULL, BASE);
    (void)res;
    if (__builtin_add_overflow(first, second, &res)) {
        printf("%d\n", 1);
    } else {
        printf("%d\n", 0);
    }

    if (second == 0 || (first == INT_MIN && second == -1)) {
        printf("%d\n", 1);
    } else {
        printf("%d\n", 0);
    }
}