#include <stdio.h>

int main()
{
    int infotype = 1, a, b, c, d;

    __asm__("cpuid"
            : "=a" (a), "=b" (b), "=c" (c), "=d" (d)
            : "0" (infotype));
    int fam, model;
    fam = (0xf00 & a) >> 8;
    model = (0xf0 & a) >> 4;
    if (fam == 6 || fam == 15) {
        model += (0xf0000 & a) >> 12;
    }
    printf ("family=%d model=%d ecx=0x%x edx=0x%x\n", fam, model, c, d);

    return 0;
}
