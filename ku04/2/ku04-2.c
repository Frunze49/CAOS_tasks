#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int separate(int fd_in, int fd_out_even, int fd_out_odd) {
    int index = 0;
    int res = 0;
    int err = 0;
    int q = 0;
    while ((q = read(fd_in, &res, sizeof(res))) != 0) {
        if (q < 0) {
            return -1;
        }
        ++index;
        lseek(fd_in, index * sizeof(int), SEEK_SET);

        if ((unsigned int)res % 2 == 0) {
            err = write(fd_out_even, &res, sizeof(res));
            if (err < 0) {
                return -1;
            }
        } else {
            err = write(fd_out_odd, &res, sizeof(res));
            if (err < 0) {
                return -1;
            }
        }
    }
    return 0;
}
