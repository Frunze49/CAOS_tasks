#include <stdio.h>
#include <stdlib.h>

int func(int eax, int ebx, int ecx, int edx) {
    return eax + ebx + ecx + edx;
}

int call_func(int eax, int ebx, int ecx, int edx) {
    int esi;
    __asm__("pushl %%ebp\n\t"
            "call func\n\t"
            "popl %%ebp"
            : "=S"(esi)
            : "a"(eax), "b"(ebx), "c"(ecx), "d"(edx));
    return esi;
}

int main() {
    printf("%d\n", call_func(-1, -2, -3, -4));
    return 0;
}