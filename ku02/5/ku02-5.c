#include <stdint.h>
#include <stdio.h>

enum {
    SEVEN_SHIFT = 7,
    FIVE_SHIFT = 5,
    THREE_SHIFT = 3,
    ONE_SHIFT = 1,
    FIRST_POWER = 1,
    SECOND_POWER = 2,
    THIRD_POWER = 4,
    FOURTH_POWER = 8,
    FIFTH_POWER = 16,
    SIXTH_POWER = 32,
    SEVENTH_POWER = 64,
    EIGHTH_POWER = 128
};

void tinyconv(uint8_t bytes[], size_t size) {
    for (int i = 0; i < size; ++i) {
        uint8_t one = (bytes[i] & FIRST_POWER) << SEVEN_SHIFT;     // 7 0
        uint8_t two = (bytes[i] & SECOND_POWER) << FIVE_SHIFT;     // 6 1
        uint8_t three = (bytes[i] & THIRD_POWER) << THREE_SHIFT;   // 5 2
        uint8_t four = (bytes[i] & FOURTH_POWER) << ONE_SHIFT;     // 4 3
        uint8_t five = (bytes[i] & FIFTH_POWER) >> ONE_SHIFT;      // 3 4
        uint8_t six = (bytes[i] & SIXTH_POWER) >> THREE_SHIFT;     // 2 5
        uint8_t seven = (bytes[i] & SEVENTH_POWER) >> FIVE_SHIFT;  // 1 6
        uint8_t eight = (bytes[i] & EIGHTH_POWER) >> SEVEN_SHIFT;  // 0 7
        bytes[i] = eight + seven + six + five + four + three + two + one;
    }
}