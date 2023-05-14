#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

union int_byte {
    int value;
    char buf[4];
};

int separate(int fd_in, int fd_out_even, int fd_out_odd) {
    int res;
    FILE *fp_even = fdopen(fd_out_even, "w");
    FILE *fp_odd = fdopen(fd_out_odd, "w");
    int q;
    int index = 0;
    while ((q = read(fd_in, &res, sizeof(res))) != 0) {
        if (q < 0) {
            return -1;
        }
        ++index;
        lseek(fd_in, index * sizeof(int), SEEK_SET);

        union int_byte tmp;
        tmp.value = res;
        if (res % 2 == 0) {
            fputs(tmp.buf, fp_even);
            if (errno != 0) {
                return -1;
            }
        } else {
            fputs(tmp.buf, fp_odd);
            if (errno != 0) {
                return -1;
            }
        }
    }

    return 0;
}


int main() {
    separate();
}