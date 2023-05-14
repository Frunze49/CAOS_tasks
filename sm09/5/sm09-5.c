#include <alloca.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma GCC optimize("O0")

enum {
    HUNDRED = 100,
};

double res = 0;

int main(int argc, char *argv[]) {
    char lib_name[HUNDRED];
    snprintf(lib_name, HUNDRED, "%s", argv[1]);

    void *handle;
    handle = dlopen(lib_name, RTLD_LAZY);

    int int_tmp;
    double double_tmp;
    int size = 0;
    char *signs = argv[3];
    for (int i = 1; i < (int)strlen(signs); ++i) {
        if (signs[i] == 'i') {
            size += sizeof(int);
        } else if (signs[i] == 'd') {
            size += sizeof(double);
        } else if (signs[i] == 's') {
            size += sizeof(char *);
        }
    }

    char *stack = alloca(size);

    for (int i = 4; i < argc; ++i) {
        if (signs[i - 3] == 'i') {
            sscanf(argv[i], "%d", &int_tmp);
            ((int *)stack)[0] = int_tmp;
            stack += sizeof(int);
        } else if (signs[i - 3] == 'd') {
            sscanf(argv[i], "%lg", &double_tmp);
            ((double *)stack)[0] = double_tmp;
            stack += sizeof(double);
        } else if (signs[i - 3] == 's') {
            ((char **)stack)[0] = argv[i];
            stack += sizeof(char *);
        }
    }

    void *ver = dlsym(handle, argv[2]);
    if (*signs == 'v') {
        asm("call %%ecx" ::"c"(ver));
    } else if (*signs == 'i') {
        int res;
        asm("call %%ecx" : "=a"(res) : "c"(ver));
        printf("%d\n", res);
    } else if (*signs == 'd') {
        asm("call %%ecx\n\t"
            "fstl res" ::"c"(ver));
        printf("%.10g\n", res);
    } else if (*signs == 's') {
        char *res;
        asm("call %%ecx" : "=a"(res) : "c"(ver));
        printf("%s\n", res);
    }
    return 0;
}
