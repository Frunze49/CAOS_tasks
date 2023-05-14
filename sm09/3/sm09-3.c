#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char *end;
    int fd = open(argv[1], O_CREAT | O_RDWR, 0777);
    int rows = (int)strtol(argv[2], &end, 10);
    int cols = (int)strtol(argv[3], &end, 10);
    if (ftruncate(fd, rows * cols * sizeof(int32_t)) != 0) {
        exit(1);
    }
    int *writer = (int *)(mmap(0, rows * cols * sizeof(int32_t), PROT_WRITE,
                               MAP_SHARED, fd, 0));
    int now = 1;

    int cur_row = 0;
    int cur_col = 0;

    for (int offset = 0; offset < ((rows + 1) / 2) && offset < ((cols + 1) / 2);
         ++offset) {
        for (int i = cur_col; i < cols; ++i) {
            if (*(writer + cur_row * cols + i) == 0) {
                *(writer + cur_row * cols + i) = now;
            } else {
                break;
            }
            ++now;
        }
        cur_col = cols - offset - 1;
        cur_row = offset + 1;

        for (int i = cur_row; i < rows; ++i) {
            if (*(writer + i * cols + cur_col) == 0) {
                *(writer + i * cols + cur_col) = now;
            } else {
                break;
            }
            ++now;
        }
        cur_row = rows - offset - 1;
        cur_col = cols - offset - 2;

        for (int i = cur_col; i >= offset; --i) {
            if (*(writer + cur_row * cols + i) == 0) {
                *(writer + cur_row * cols + i) = now;
            } else {
                break;
            }
            ++now;
        }
        cur_col = offset;
        cur_row = rows - offset - 2;

        for (int i = cur_row; i >= offset + 1; --i) {
            if (*(writer + i * cols + cur_col) == 0) {
                *(writer + i * cols + cur_col) = now;
            } else {
                break;
            }

            ++now;
        }
        cur_col = offset + 1;
        cur_row = offset + 1;
    }

    return 0;
}