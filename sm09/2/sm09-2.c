#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    double mid = 0;
    struct stat buff_stat;
    int fd;

    FILE *fp = fopen(argv[1], "r");
    fd = fileno(fp);
    fstat(fd, &buff_stat);
    double *start =
        (double *)(mmap(0, buff_stat.st_size, PROT_READ, MAP_SHARED, fd, 0));
    for (int i = 0; i < buff_stat.st_size / sizeof(mid); ++i) {
        mid += start[i];
    }

    printf("%a\n", mid / (buff_stat.st_size / sizeof(mid)));
    fclose(fp);

    return 0;
}