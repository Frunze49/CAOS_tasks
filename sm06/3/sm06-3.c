#include <stdio.h>

enum {
    LOW_KIRILL = 0x0400,
    UP_KIRILL = 0x04ff,
    TWO_BYTE_UTF = 6,
    THREE_BYTE_UTF = 14,
    OFFSET = 0x1f,
    ONE_BYTE_UTF_CHECK = 7,
    PADDING = 0x3f
};

int main(void) {
    unsigned char p;
    int letter_counter = 0, kirill_counter = 0;
    while (scanf("%c", &p) == 1) {
        int now_letter = 0;
        if (p >> ONE_BYTE_UTF_CHECK == 0) {
            //
        } else if (p >> 5 == TWO_BYTE_UTF) {
            now_letter = (int)p;
            now_letter &= OFFSET;
            if (scanf("%c", &p) == 1) {
                now_letter = now_letter << 6;
                now_letter += (p & PADDING);
            }
        } else if (p >> 4 == THREE_BYTE_UTF) {
            if (scanf("%c", &p) != 1) {
                return -1;
            }
            if (scanf("%c", &p) != 1) {
                return -1;
            }
        } else {
            if (scanf("%c", &p) != 1) {
                return -1;
            }
            if (scanf("%c", &p) != 1) {
                return -1;
            }
            if (scanf("%c", &p) != 1) {
                return -1;
            }
        }
        if (now_letter >= LOW_KIRILL && now_letter <= UP_KIRILL) {
            ++kirill_counter;
        }
        ++letter_counter;
    }
    printf("%d %d\n", letter_counter, kirill_counter);
    return 0;
}
