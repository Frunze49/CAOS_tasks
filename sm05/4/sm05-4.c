#include <ctype.h>
#include <stdio.h>

int main(void) {
    int sum = 0;
    int s;
    int *tmp = &s;
    while ((*tmp = getchar()) != EOF) {
        if (isdigit(s)) {
            sum += (int)(s - '0');
        }
    }
    printf("%d\n", sum);
    return 0;
}
