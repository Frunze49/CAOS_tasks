#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat buf;
    for (int i = 1; i < argc; ++i) {
        int tmp = lstat(argv[i], &buf);
        if (tmp != -1) {
            tmp = stat(argv[i], &buf);
            if (tmp == -1) {
                printf("%s (broken symlink)\n", argv[i]);
            } else {
                printf("%s\n", argv[i]);
            }
        } else {
            printf("%s (missing)\n", argv[i]);
        }
    }
    return 0;
}