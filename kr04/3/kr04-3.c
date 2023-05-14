#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

enum {
    NODE_SIZE = 12, MAGIC = 1000
};

struct Node {
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

struct Node read_node(int index, int fd, int *reader) {
    struct Node new_node = *(struct Node *)(reader + index * 3);
    return new_node;
}

void write_key(struct Node node, int fd, int *reader) {
    if (node.right_idx != 0) {
        struct Node right_node = read_node(node.right_idx, fd, reader);
        write_key(right_node, fd, reader);
    }

    printf("%d ", node.key);

    if (node.left_idx != 0) {
        struct Node right_node = read_node(node.left_idx, fd, reader);
        write_key(right_node, fd, reader);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        int fd = open(argv[1], O_RDONLY);
        struct stat s;
        int status = fstat (fd, & s);
        (void)status;
        int size = s.st_size;

        int *reader = (int *)(mmap(0, size, PROT_READ,
                                   MAP_SHARED, fd, 0));
        struct Node node = read_node(0, fd, reader);
        write_key(node, fd, reader);
        printf("\n");
    } else {
        exit(1);
    }
    return 0;
}
