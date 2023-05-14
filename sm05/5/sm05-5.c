#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "poliz.h"

enum { INT_MIN = -2147483648, BUFF_SIZE = 15 };

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

struct PolizState {
    Node *head;
    Node *end;
    int size;
    int err;
};

int push(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (state->size == 0) {
        state->head->value = iextra;
        ++state->size;
        state->err = PE_OK;
    } else {
        Node *node;
        node = calloc(1, sizeof(*node));
        if (node == NULL) {
            state->err = PE_OUT_OF_MEMORY;
            free(node);
        } else {
            node->value = iextra;
            node->next = state->head;
            state->head->prev = node;
            state->head = node;
            ++state->size;
            state->err = PE_OK;
        }
    }
    return -state->err;
}

int plus(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (state->size < 2) {
        state->err = PE_STACK_UNDERFLOW;
    } else {
        int res = 0;
        if (__builtin_add_overflow(state->head->value, state->head->next->value,
                                   &res)) {
            state->err = PE_INT_OVERFLOW;
        } else {
            state->head->next->value = res;
            state->head = state->head->next;
            free(state->head->prev);
            --state->size;
            state->err = PE_OK;
        }
    }
    (void)iextra;
    return -state->err;
}

int minus(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (state->size < 2) {
        state->err = PE_STACK_UNDERFLOW;
    } else {
        int res = 0;
        if (__builtin_sub_overflow(state->head->next->value, state->head->value,
                                   &res)) {
            state->err = PE_INT_OVERFLOW;
        } else {
            state->head->next->value = res;
            state->head = state->head->next;
            free(state->head->prev);
            --state->size;
            state->err = PE_OK;
        }
    }
    (void)iextra;
    return -state->err;
}

int mul(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (state->size < 2) {
        state->err = PE_STACK_UNDERFLOW;
    } else {
        int res = 0;
        if (__builtin_mul_overflow(state->head->value, state->head->next->value,
                                   &res)) {
            state->err = PE_INT_OVERFLOW;
        } else {
            state->head->next->value = res;
            state->head = state->head->next;
            free(state->head->prev);
            --state->size;
            state->err = PE_OK;
        }
    }
    (void)iextra;
    return -state->err;
}

int division(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (state->size < 2) {
        state->err = PE_STACK_UNDERFLOW;
    } else {
        if (state->head->value == 0) {
            state->err = PE_DIVISION_BY_ZERO;
        } else if (state->head->value == -1 &&
                   state->head->next->value == INT_MIN) {
            state->err = PE_INT_OVERFLOW;
        } else {
            int offset = 0;
            int res;
            int f = state->head->next->value, s = state->head->value;
            if (f % s != 0) {
                if (f / s < 0) {
                    offset = 1;
                } else {
                    offset = -1;
                }
            }
            if (f > 0) {
                res = f / s;
            } else {
                res = f / s - offset;
            }
            state->head->next->value = res;
            state->head = state->head->next;
            state->err = PE_OK;
            free(state->head->prev);
            --state->size;
        }
    }
    (void)iextra;
    return -state->err;
}

int perc(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (state->size < 2) {
        state->err = PE_STACK_UNDERFLOW;
    } else {
        if (state->head->value == 0) {
            state->err = PE_DIVISION_BY_ZERO;
        } else {
            int res = state->head->next->value % state->head->value;
            if (res < 0) {
                res += abs(state->head->value);
            }
            state->head->next->value = res;
            state->head = state->head->next;
            state->err = PE_OK;
            free(state->head->prev);
            --state->size;
        }
    }
    (void)iextra;
    return -state->err;
}

int hash(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (state->size == 0) {
        state->err = PE_STACK_UNDERFLOW;
    } else {
        int res = 0;
        if (__builtin_mul_overflow(state->head->value, -1, &res)) {
            state->err = PE_INT_OVERFLOW;
        } else {
            state->head->value = res;
            state->err = PE_OK;
        }
    }
    (void)iextra;
    return -state->err;
}

int read(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (state->size == 0) {
        if (scanf("%d", &state->head->value) == 0) {
            state->err = PE_READ_FAILED;
        } else {
            ++state->size;
            state->err = PE_OK;
        }
    } else {
        Node *node;
        node = calloc(1, sizeof(*node));
        if (node == NULL) {
            state->err = PE_OUT_OF_MEMORY;
            free(node);
        } else {
            node->next = state->head;
            state->head->prev = node;
            state->head = node;
            if (scanf("%d", &state->head->value) == 0) {
                state->err = PE_READ_FAILED;
                free(node);
            } else {
                state->err = PE_OK;
                ++state->size;
            }
        }
    }
    (void)iextra;
    return -state->err;
}

int semicolon(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (state->size == 0) {
        state->err = PE_STACK_UNDERFLOW;
    } else if (state->size == 1) {
        state->size = 0;
        state->err = PE_OK;
    } else {
        state->head = state->head->next;
        free(state->head->prev);
        --state->size;
        state->err = PE_OK;
    }
    (void)iextra;
    return -state->err;
}

int write(struct PolizState *state, int iextra) {
    if (state->err) {
        return -state->err;
    } else if (state->size == 0) {
        state->err = PE_STACK_UNDERFLOW;
        return -state->err;
    }
    printf("%d", state->head->value);
    return semicolon(state, iextra);
}

int nline(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else {
        printf("\n");
        state->err = PE_OK;
    }
    (void)iextra;
    return -state->err;
}

int dnum(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (state->size < iextra + 1) {
        state->err = PE_INVALID_INDEX;
    } else {
        Node *tmp_node = state->head;
        for (int i = 0; i < iextra; ++i) {
            tmp_node = tmp_node->next;
        }

        Node *node;
        node = calloc(1, sizeof(*node));
        if (node == NULL) {
            state->err = PE_OUT_OF_MEMORY;
        } else {
            node->value = tmp_node->value;
            node->next = state->head;
            state->head->prev = node;
            state->head = node;

            ++state->size;
            state->err = PE_OK;
        }
    }
    return -state->err;
}

int snum(struct PolizState *state, int iextra) {
    if (state->err) {
        //
    } else if (iextra == 0) {
        state->err = PE_OK;
    } else if (state->size < iextra + 1) {
        state->err = PE_INVALID_INDEX;
    } else {
        Node *tmp_node = state->head;
        for (int i = 0; i < iextra; ++i) {
            tmp_node = tmp_node->next;
        }
        int tmp = state->head->value;
        state->head->value = tmp_node->value;
        tmp_node->value = tmp;

        state->err = PE_OK;
    }
    return -state->err;
}

struct PolizItem *poliz_compile(const char *str) {
    struct PolizItem *items;
    items = calloc(1, sizeof(*items));
    if (items == NULL) {
        return NULL;
    }

    int capacity = 1;
    int size = 0;

    char buf[BUFF_SIZE];
    int char_count;

    while (sscanf(str, "%s%n", buf, &char_count) == 1) {
        while (*str == ' ') {
            str += 1;
        }
        sscanf(str, "%s%n", buf, &char_count);
        if (buf[0] == '\0') {
            break;
        }
        if (size + 1 == capacity) {
            struct PolizItem *new_items = (struct PolizItem *)realloc(
                items, 2 * capacity * sizeof(*items));
            items = new_items;
            capacity *= 2;
        }

        if (buf[0] == '+') {
            if (char_count > 1) {
                items[size].handler = push;
                if (sscanf(str + 1, "%d", &items[size].iextra) == 0) {
                    return NULL;
                }
            } else {
                items[size].handler = plus;
            }
            ++size;
        } else if (buf[0] == '-') {
            if (char_count > 1) {
                items[size].handler = push;
                if (sscanf(str, "%d", &items[size].iextra) == 0) {
                    return NULL;
                }
            } else {
                items[size].handler = minus;
            }
            ++size;
        } else if (buf[0] == '*') {
            items[size].handler = mul;
            ++size;
        } else if (buf[0] == '/') {
            items[size].handler = division;
            ++size;
        } else if (buf[0] == '%') {
            items[size].handler = perc;
            ++size;
        } else if (buf[0] == '#') {
            items[size].handler = hash;
            ++size;
        } else if (buf[0] == 'r') {
            items[size].handler = read;
            ++size;
        } else if (buf[0] == 'w') {
            items[size].handler = write;
            ++size;
        } else if (buf[0] == 'n') {
            items[size].handler = nline;
            ++size;
        } else if (buf[0] == ';') {
            items[size].handler = semicolon;
            ++size;
        } else if (buf[0] == 'd') {
            items[size].handler = dnum;
            if (char_count > 1) {
                items[size].handler = dnum;
                if (sscanf(str + 1, "%d", &items[size].iextra) == 0) {
                    return NULL;
                }
            } else {
                items[size].iextra = 0;
            }
            ++size;
        } else if (buf[0] == 's') {
            items[size].handler = snum;
            if (char_count > 1) {
                items[size].handler = snum;
                if (sscanf(str + 1, "%d", &items[size].iextra) == 0) {
                    return NULL;
                }
            } else {
                items[size].iextra = 1;
            }
            ++size;
        } else if (isdigit(buf[0])) {
            items[size].handler = push;
            if (sscanf(str, "%d", &items[size].iextra) == 0) {
                return NULL;
            }
            ++size;
        }
        str += char_count;
    }
    items[size].handler = NULL;
    return items;
}

struct PolizState *poliz_new_state(void) {
    struct PolizState *array;
    array = calloc(1, sizeof(*array));
    if (array == NULL) {
        array->err = PE_OUT_OF_MEMORY;
    } else {
        array->size = 0;
        array->err = 0;
        array->head = calloc(1, sizeof(*array->head));
        array->end = array->head;
    }
    return array;
}

void poliz_free_state(struct PolizState *state) {
    while (state->head != state->end) {
        state->end = state->end->prev;
        free(state->end->next);
    }
    free(state->head);
    free(state);
}

int poliz_last_error(struct PolizState *state) {
    return state->err;
}
