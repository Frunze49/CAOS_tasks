#include "drivers/vga.h"
#include <stdarg.h>
#include "drivers/uart.h"

void kprintf(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    while (*fmt != '\0') {
        if(*fmt == '%') {
            unsigned arg = va_arg(ap, unsigned);
            ++fmt;
            char type = *fmt;
            if (type == 'x') {
                char arr[10];
                int i = 0;
                if (arg == 0) {
                    uartputc('0');
                } else {
                    while (arg != 0) {
                        arr[i] = arg % 0x10;

                        ++i;
                        arg /= 0x10;
                    }
                    while(i > 0) {
                        if (arr[i - 1] < 10) {
                            uartputc(arr[i - 1] + '0');
                        } else {
                            uartputc(arr[i - 1] - 10 + 'a');
                        }

                        --i;
                    }
                }
            } else {
                char arr[10];
                int i = 0;
                if (arg == 0) {
                    uartputc('0');
                } else {
                    while (arg != 0) {
                        arr[i] = arg % 10;

                        ++i;
                        arg /= 10;
                    }
                    while(i > 0) {
                        uartputc(arr[i - 1] + '0');
                        --i;
                    }
                }
            }
        } else {
            uartputc(*fmt);
        }
        ++fmt;
    }
    va_end(ap);
}