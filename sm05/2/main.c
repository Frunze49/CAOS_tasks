#include <stdio.h>
typedef struct BSearchResult {
    size_t low;
    size_t high;
    int result;
} BSearchResult;
typedef struct BSearchResult BSearchResult;
BSearchResult bsearch2(const void *key, const void *base, size_t nmemb, size_t size,
         int (*compar)(const void *p1, const void *p2, void *user),
         void *user);
int compar(const void *lhs, const void *rhs, void *) {
    return *(int *) lhs - *(int *) rhs;
}

int main(void) {
    int arr[] = {1, 1, 1, 3, 4};
    int key = 2;
    struct BSearchResult result = bsearch2(&key, arr, 5, 4, compar, NULL);
    printf("%ld %ld %d\n", result.low, result.high, result.result);
    return 0;
}
