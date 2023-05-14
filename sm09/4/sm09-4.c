#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    double var = 0;
    void *handle;
    handle = dlopen("libm.so.6", RTLD_LAZY);
    double (*ver)(double) = (double (*)(double))dlsym(handle, argv[1]);
    while (scanf("%lg", &var) != EOF) {
        printf("%.10g\n", ver(var));
    }
    return 0;
}