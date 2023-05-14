#include <stdio.h>

void computation(float *a, int b, float *c);



int main() {
    float a[] = {1., 2., 3., 4., -1., 2., 14., -12., 0., 12., 1., 2.};
    float c = 0;
    computation(a, 12, &c);
    printf("%f\n", c);
}