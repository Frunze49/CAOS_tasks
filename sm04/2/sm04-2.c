#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    uint64_t num;
    bool flag = false;
    while (scanf("%llx", &num) == 1) {
        if (flag) {
            printf(" ");
        }
        if (num == 0) {
            printf("%x", -1);
        }
        int index = 0;
        uint64_t prev = 0, now = 1;
        while (prev + now <= num) {
            now += prev;
            prev = now - prev;
            ++index;
        }
        flag = true;
        printf("%x", index);
    }
    printf("\n");
    return 0;
}
