#include <stdio.h>

#include "sm05-1.c"

int main(void) {
    RandomGenerator *rr = random_create(1234);
    for (int j = 0; j < 10; ++j) {
        printf("%d\n", rr->ops->next(rr));
    }
    rr->ops->destroy(rr);
    return 0;
}
