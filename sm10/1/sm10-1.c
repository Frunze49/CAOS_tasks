
enum { CHAR_MAX = 255 };

union FloatToBytes {
    float value;

    struct {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;

    } bytes;
};

FPClass fpclassf(float value, int *psign) {
    union FloatToBytes tmp;
    tmp.value = value;
    *psign = tmp.bytes.sign;
    if (tmp.bytes.exponent == 0) {
        if (tmp.bytes.mantissa == 0) {
            return FFP_ZERO;
        }
        return FFP_DENORMALIZED;
    } else if (tmp.bytes.exponent == CHAR_MAX) {
        if (tmp.bytes.mantissa == 0) {
            return FFP_INF;
        } else {
            *psign = 0;
            return FFP_NAN;
        }
    } else {
        return FFP_NORMALIZED;
    }
}
