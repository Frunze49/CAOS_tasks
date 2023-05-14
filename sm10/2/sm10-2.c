#include <stdio.h>

union FloatToBytes {
    float value;

    struct {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;

    } bytes;
};

int main() {
    float x;
    while (scanf("%f", &x) == 1) {
        union FloatToBytes tmp;
        tmp.value = x;
        printf("%d %d %x\n", tmp.bytes.sign, tmp.bytes.exponent,
               tmp.bytes.mantissa);
    }
    return 0;
}