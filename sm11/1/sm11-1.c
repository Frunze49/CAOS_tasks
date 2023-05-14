#include <stdio.h>
#include <unistd.h>

enum { T = 1000, TT = 2000 };

int main() {
    pid_t res = fork();
    if (res < 0) {
        perror("fork\n");
        return 1;
    } else if (res == 0) {
        pid_t s_res = fork();
        if (s_res < 0) {
            perror("fork\n");
            return 1;
        } else if (s_res == 0) {
            printf("%d ", 3);
        } else {
            usleep(T);
            printf("%d ", 2);
        }
    } else {
        usleep(TT);
        printf("%d\n", 1);
    }

    return 0;
}