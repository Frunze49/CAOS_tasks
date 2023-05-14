#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void my_func(char *f_dir, char *n_dir, char *l_dir, int max_size, int depth) {
    if (!access(f_dir, R_OK)) {
        char full_dir[PATH_MAX];
        snprintf(full_dir, PATH_MAX, "%s", f_dir);

        char now_dir[PATH_MAX];
        snprintf(now_dir, PATH_MAX, "%s", n_dir);

        char last_dir[PATH_MAX];
        snprintf(last_dir, PATH_MAX, "%s", l_dir);

        struct dirent *obj;

        DIR *dir = opendir(full_dir);
        while ((obj = readdir(dir)) != NULL) {
            if (strcmp(obj->d_name, ".") == 0 ||
                strcmp(obj->d_name, "..") == 0) {
                continue;
            }
            char dir_path[PATH_MAX];
            char slash[] = "/";
            int cx = snprintf(dir_path, PATH_MAX, "%s", full_dir);
            if (full_dir[strlen(full_dir) - 2] != '/') {
                cx += snprintf(dir_path + cx, PATH_MAX - cx, "%s", slash);
            }
            cx += snprintf(dir_path + cx, PATH_MAX - cx, "%s", obj->d_name);

            char rel_path[PATH_MAX];
            int dx = snprintf(rel_path, PATH_MAX, "%s", now_dir);

            dx += snprintf(rel_path + dx, PATH_MAX - dx, "%s", obj->d_name);

            struct stat path_stat;

            lstat(dir_path, &path_stat);
            if (S_ISLNK(path_stat.st_mode)) {
                continue;
            }
            stat(dir_path, &path_stat);
            if (S_ISREG(path_stat.st_mode) && path_stat.st_size <= max_size) {
                if (!access(dir_path, R_OK)) {
                    printf("%s\n", rel_path);
                }
            } else if (depth < 3) {

                cx += snprintf(dir_path + cx, PATH_MAX - cx, "%s", slash);
                dx += snprintf(rel_path + dx, PATH_MAX - dx, "%s", slash);

                my_func(dir_path, rel_path, obj->d_name, max_size, depth + 1);
            }
        }
        closedir(dir);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 3) {

        char *full_dir = argv[1];
        char *now_dir = "";
        char *last = "";
        int max_size;
        if (sscanf(argv[2], "%d", &max_size) == 0) {
            exit(1);
        }

        my_func(full_dir, now_dir, last, max_size, 0);

    } else {
        exit(1);
    }

    return 0;
}