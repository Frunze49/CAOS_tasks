#include <stdio.h>
#include <string.h>

enum {BUFF_SIZE = 1024};

int main(int argc, char *argv[]) {
    char *first[BUFF_SIZE], *second[BUFF_SIZE];
    int flag = 0, size = 0;
    for (int i = 1; i < argc; ++i) {
        printf("%d\n", argc);
        if (argv[i][0] == ';' && strlen(argv[i]) == 1) {
            flag = 1;
            size = i - 1;
            first[i - 1] = NULL;
            continue ;
        }
        if (flag) {
            second[i - size - 2] = argv[i];
        } else {
            first[i - 1] = argv[i];
        }
    }
    second[argc - size - 2] = NULL;
    printf("%s\n", argv[5]);
//    for (int i = 0; i < argc - size - 2; ++i) {
//        printf("%s\n", second[i]);
//    }

    return 0;
}