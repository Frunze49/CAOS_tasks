enum { CHAR_MAX = 255, FLOAT_MAX = 8388607, TT = 22 };

union FloatToBytes {
    float value;

    struct {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;

    } bytes;
};

void sat_mul8(float *f) {
    union FloatToBytes tmp;
    tmp.value = *f;

    if (tmp.bytes.exponent == CHAR_MAX) {
        return;
    } else if (tmp.bytes.exponent + 3 < CHAR_MAX) {
        if (tmp.bytes.exponent == 0) {
            int flag = 0;
            for (int i = 0; i < 3; ++i) {
                if (!(tmp.bytes.mantissa & (1 << TT)) && !flag) {
                    tmp.bytes.mantissa = tmp.bytes.mantissa << 1;
                } else {
                    if (flag == 0) {
                        tmp.bytes.mantissa = tmp.bytes.mantissa << 1;
                        flag = 1;
                    }
                    tmp.bytes.exponent += 1;
                }
            }
        } else {
            tmp.bytes.exponent += 3;
        }
    } else {
        tmp.bytes.exponent = CHAR_MAX - 1;
        tmp.bytes.mantissa = FLOAT_MAX;
    }
    *f = tmp.value;
}

//
// int main() {
//     float a = 3.51270772804e-39, b = 3.51270772804e-39;
//     sat_mul8(&a);
//     printf("%.10g, %.10g\n", a, 8 * b);
//     return 0;
// }
