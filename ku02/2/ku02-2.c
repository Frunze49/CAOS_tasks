#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>

Node *push(Node *place, int value) {
    Node *tmp;
    tmp = calloc(1, sizeof(*tmp));
    if (tmp == NULL) {
        return NULL;
    }
    tmp->value = value;
    if (place != NULL) {
        tmp->next = place;
        if (place->prev != NULL) {
            tmp->prev = place->prev;
            place->prev->next = tmp;
        }
        place->prev = tmp;
    }
    return tmp;
}

int pop(Node *node) {
    int ans = node->value;
    if (node->prev != NULL && node->next != NULL) {
        node->next->prev = node->prev;
        node->prev->next = node->next;
    } else if (node->next != NULL) {
        node->next->prev = NULL;
    } else if (node->prev != NULL) {
        node->prev->next = NULL;
    }
    free(node);
    return ans;
}
