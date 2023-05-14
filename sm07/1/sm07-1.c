#include "drivers/vga.h"

unsigned new_line(unsigned row, unsigned offset) {
    return (row * COLS) + (offset / COLS);
}

void show_vga_symbol_table(void) {
    unsigned offset = 0;
    unsigned row = 0;
    vga_clear_screen();

    vga_set_char(offset, ' ');
    ++offset;
    vga_set_char(offset, ' ');
    ++offset;

    for (int i = 0x0; i <= 0xf; ++i) {
        if (i < 0xa) {
            vga_set_char(offset, i + '0');
        } else {
            vga_set_char(offset, (i - 0xa) + 'a');
        }
        ++offset;
        vga_set_char(offset, ' ');
        ++offset;
    }
    ++row;
    offset = new_line(row, offset);

    for (int i = 0x0; i <= 0xf; ++i) {
        if (i < 0xa) {
            vga_set_char(offset, i + '0');
        } else {
            vga_set_char(offset, (i - 0xa) + 'a');
        }
        ++offset;
        vga_set_char(offset, ' ');
        ++offset;
        for (int j = 0x0; j <= 0xf; ++j) {
            vga_set_char(offset, 0x10 * i + j);
            ++offset;
            vga_set_char(offset, ' ');
            ++offset;
        }
        ++row;
        offset = new_line(row, offset) - i - 1;
    }
}
