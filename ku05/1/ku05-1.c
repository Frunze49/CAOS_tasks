#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { BUFF_SIZE = 1024, NINETEEN = 19 };

int main(int argc, char *argv[]) {
    int status1 = 0, status2 = 0;
    int fd[2];
    if (pipe(fd) < 0) {
        perror("pipe\n");
    }
    if (!fork()) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        close(fd[0]);

        char command[BUFF_SIZE] = "void foo() { ";
        int size = strlen(command);
        size += snprintf(command + size, BUFF_SIZE, "%s; }", argv[1]);

        execlp("echo", "echo", command, (char *)NULL);
    }
    close(fd[1]);

    if (!fork()) {
        dup2(fd[0], STDIN_FILENO);
        int dev_null = open("/dev/null", O_WRONLY);
        dup2(dev_null, STDERR_FILENO);
        dup2(dev_null, STDOUT_FILENO);
        close(fd[0]);
        if (system("gcc -x c -c -o /dev/null -") != 0) {
            exit(1);
        } else {
            exit(0);
        }
    }

    close(fd[0]);
    wait(&status1);
    wait(&status2);
    if (WEXITSTATUS(status1) == 0 && WEXITSTATUS(status2) == 0) {
        printf("Valid\n");
    } else {
        printf("Invalid\n");
    }
    return 0;
}