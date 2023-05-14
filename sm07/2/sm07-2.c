#include "drivers/port.h"
#include "drivers/vga.h"

unsigned char get_color(unsigned char fg, unsigned char bg) {
    return (bg << 4) + fg;
}

void scroll() {
    for (unsigned i = 0; i < COLS * (ROWS - 1); ++i) {
        video_memory[2 * i] = video_memory[2 * (i + COLS)];
        video_memory[2 * i + 1] = get_color(light_gray, black);
    }
    for (unsigned i = COLS * (ROWS - 1); i < COLS * ROWS; ++i) {
        video_memory[2 * i] = ' ';
        video_memory[2 * i + 1] = get_color(light_gray, black);
    }
}

unsigned new_line(unsigned row, unsigned offset) {
    return (row * COLS) + (offset / COLS);
}

void vga_set_cursor(unsigned offset) {
    unsigned low = offset & 0x00ff;
    unsigned high = (offset & 0xff00) >> 8;

    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    port_byte_out(VGA_DATA_REGISTER, low);

    port_byte_out(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    port_byte_out(VGA_DATA_REGISTER, high);
}

void vga_putc(char c) {
    unsigned offset = vga_get_cursor();
    if (c == 0xa) {
        if (offset / COLS == ROWS - 1) {
            scroll();
            vga_set_cursor(COLS * (ROWS - 1));
        } else {
            offset = new_line(offset / COLS, offset);
            vga_set_cursor(offset + COLS);
        }
    } else if (offset == COLS * ROWS - 1) {
        vga_set_char(offset, c);
        scroll();
        vga_set_cursor(COLS * (ROWS - 1));
    } else {
        vga_set_char(offset, c);
        vga_set_cursor(offset + 1);
    }
}