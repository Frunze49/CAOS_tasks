#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

enum {
    NODE_SIZE = 12,
};

struct Node {
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

struct Node read_node(int index, int fd) {
    struct Node new_node;
    lseek(fd, index * NODE_SIZE, SEEK_SET);
    if (read(fd, &new_node, sizeof(new_node)) < 0) {
        exit(1);
    }
    return new_node;
}

void write_key(struct Node node, int fd) {
    if (node.right_idx != 0) {
        struct Node right_node = read_node(node.right_idx, fd);
        write_key(right_node, fd);
    }

    printf("%d ", node.key);

    if (node.left_idx != 0) {
        struct Node right_node = read_node(node.left_idx, fd);
        write_key(right_node, fd);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int fd = open(argv[1], O_RDONLY);
        struct Node node = read_node(0, fd);
        write_key(node, fd);
        printf("\n");
    } else {
        exit(1);
    }
    return 0;
}