#include <stdint.h>
#include <stdio.h>

int main(void) {
    int a, b, n;
    if (scanf("%d%d%d", &a, &b, &n) == 0) {
        return 1;
    }

    printf("%*s", n, "");
    for (int i = a; i < b; ++i) {
        printf(" %*d", n, i);
    }
    printf("\n");

    for (int i = a; i < b; ++i) {
        printf("%*d", n, i);
        for (int j = a; j < b; ++j) {
            int64_t res = (int64_t)i * (int64_t)j;
            printf(" %*lld", n, res);
        }
        printf("\n");
    }
    return 0;
}
