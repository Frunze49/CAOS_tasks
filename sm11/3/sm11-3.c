#include "sys/wait.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int f_in = open(argv[2], O_RDONLY);
    int f_out = open(argv[3], O_TRUNC | O_CREAT | O_RDWR, 0666);
    int res = fork();
    if (res < 0) {
        return 0;
    } else if (res == 0) {
        dup2(f_out, STDOUT_FILENO);
        dup2(f_in, STDIN_FILENO);
        close(f_out);
        close(f_in);
        execlp(argv[1], argv[1], argv);
    } else {
        wait(NULL);
    }

    return 0;
}