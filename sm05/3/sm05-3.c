#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List {
    Node *head;
    Node *end;
    int size;
} List;

int main(void) {
    List *new_list;
    new_list = calloc(1, sizeof(*new_list));
    new_list->size = 0;

    int tmp;
    while (scanf("%d", &tmp) == 1) {
        Node *new_node;
        new_node = calloc(1, sizeof(*new_node));
        new_node->value = tmp;

        if (new_list->size == 0) {
            new_list->head = new_node;
            new_list->end = new_node;
            new_list->size = 1;
        } else {
            new_node->prev = new_list->end;
            new_list->end->next = new_node;
            new_list->end = new_node;
            ++new_list->size;
        }
    }
    if (new_list->size == 0) {
        free(new_list);
        return 0;
    }
    Node *go = new_list->end;
    while (go != new_list->head) {
        printf("%d\n", go->value);
        go = go->prev;
        free(go->next);
    }
    printf("%d\n", go->value);
    free(go);
    free(new_list);
    return 0;
}
