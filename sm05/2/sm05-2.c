#include <stddef.h>

struct BSearchResult {
    size_t low;
    size_t high;
    int result;
};

struct BSearchResult
bsearch2(const void *key, const void *base, size_t nmemb, size_t size,
         int (*compar)(const void *p1, const void *p2, void *user),
         void *user) {
    struct BSearchResult answer;
    if (nmemb == 0) {
        answer.low = 0;
        answer.high = 0;
        answer.result = 0;
        return answer;
    } else if (nmemb == 1) {
        const void *mid = base;
        if (compar(mid, key, user) > 0) {
            answer.low = 0;
            answer.high = 0;
            answer.result = 0;
        } else if (compar(mid, key, user) < 0) {
            answer.low = nmemb;
            answer.high = nmemb;
            answer.result = 0;
        } else {
            answer.low = 0;
            answer.high = nmemb;
            answer.result = 1;
        }
        return answer;
    } else if (compar(base + size * (nmemb - 1), key, user) < 0) {
        answer.low = nmemb;
        answer.high = nmemb;
        answer.result = 0;
        return answer;
    } else if (compar(base, key, user) > 0) {
        answer.low = 0;
        answer.high = 0;
        answer.result = 0;
        return answer;
    }

    size_t left = 0, right = nmemb - 1;
    while (left < right) {
        const void *mid = base + size * ((left + right) / 2);
        if (compar(mid, key, user) >= 0) {
            right = (left + right) / 2;
        } else {
            left = (left + right) / 2 + 1;
        }
    }
    answer.low = left;

    left = 0, right = nmemb - 1;
    while (left < right) {
        const void *mid = base + size * ((left + right) / 2);
        if (compar(mid, key, user) <= 0) {
            left = (left + right) / 2 + 1;
        } else {
            right = (left + right) / 2;
        }
    }

    if (compar(base + size * left, key, user) == 0 && left == nmemb - 1) {
        answer.high = nmemb;
    } else {
        answer.high = left;
    }

    if (answer.high != answer.low) {
        answer.result = 1;
    } else {
        answer.result = 0;
    }
    return answer;
}
