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
        place->prev = tmp;
    }
    return tmp;
}

int pop(Node *node) {
    int ans = node->value;
    if (node->prev != NULL && node->next != NULL) {
        Node *tmp = node->next;
        node->next = node->prev;
        node->prev = tmp;
    }
    free(node);
    return ans;
}
