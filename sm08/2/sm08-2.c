#include "read_file.h"
#include <errno.h>
#include <malloc.h>
#include <unistd.h>

enum {
    BUFF_SIZE = 4096,
};

struct FileContent read_file(int fd) {
    struct FileContent result;
    result.size = 0;
    result.data = calloc(1, sizeof(result.data));
    char buff[BUFF_SIZE];
    ssize_t tmp;
    errno = 0;

    while ((tmp = read(fd, buff, BUFF_SIZE)) > 0) {
        result.size += tmp;

        char *old;
        if ((old = realloc(result.data, result.size + 1)) == NULL) {
            free(result.data);
            result.size = -1;
            result.data = NULL;
            return result;
        }
        result.data = old;
        for (int i = result.size - tmp; i < result.size; ++i) {
            result.data[i] = buff[i - result.size + tmp];
        }
        result.data[result.size] = '\0';

        errno = 0;
    }

    if (tmp < 0 && errno) {
        result.size = -1;
        free(result.data);
        result.data = NULL;
        return result;
    }

    return result;
}

// int main() {
//     struct FileContent ans = read_file(0);
//
//     printf("%ld\n%s\n", ans.size, ans.data);
//     free(ans.data);
//     return 0;
// }