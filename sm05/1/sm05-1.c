#include <stdlib.h>

enum Consts { A = 1103515245, C = 12345, MOD = 2147483648 };

struct RandomGenerator;

typedef struct RandomOperations {
    void (*destroy)(struct RandomGenerator *rr);
    unsigned int (*next)(struct RandomGenerator *rr);
} RandomOperations;

typedef struct RandomGenerator {
    unsigned int value;
    RandomOperations *ops;
} RandomGenerator;

static void destroy(RandomGenerator *rr) {
    free(rr->ops);
    free(rr);
}

static unsigned int next(RandomGenerator *rr) {
    rr->value = ((unsigned int)A * (unsigned int)rr->value + (unsigned int)C) %
                (unsigned int)MOD;
    return rr->value;
}

RandomGenerator *random_create(int seed) {
    RandomGenerator *rr;
    rr = calloc(1, sizeof(*rr));
    if (rr == NULL) {
        return NULL;
    }
    rr->value = (unsigned int)seed;
    rr->ops = calloc(1, sizeof(*rr));
    if (rr->ops == NULL) {
        return NULL;
    }
    rr->ops->next = next;
    rr->ops->destroy = destroy;
    return rr;
}
