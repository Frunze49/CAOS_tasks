#include <sys/syscall.h>

enum {
    BUFF_SIZE = 0x1000,
};

struct FileWriteState {
    int fd;  // "файловый дескриптор", для вывода на стандартный поток вывода -
             // 1
    unsigned char *buf;  // указатель на буфер
    int bufsize;         // размер буфера
    int real_size;  // здесь потребуется добавить поля для реализации
                    // буферизованной записи
};

unsigned char buffer[BUFF_SIZE];
struct FileWriteState stout_obj = {
    .fd = 1, .buf = buffer, .bufsize = BUFF_SIZE, .real_size = 0};
struct FileWriteState *stout = &stout_obj;

void flush(struct FileWriteState *out) {
    int ret;
    asm volatile("int $0x80"
                 : "=a"(ret)
                 : "a"(SYS_write), "b"(out->fd), "c"(out->buf),
                   "d"(out->real_size));
}

void writechar(int c, struct FileWriteState *out) {
    out->buf[out->real_size] = (unsigned char)c;
    ++out->real_size;

    if (out->real_size == out->bufsize) {
        flush(out);
        out->real_size = 0;
    }
}

// int main() {
//     for (int i = 0; i < 4100; ++i) {
//         writechar('a', stout);
//     }
//     writechar('b', stout);
//     flush(stout);
//     writechar('c', stout);
//     return 0;
// }
