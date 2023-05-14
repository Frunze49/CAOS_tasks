#include "stdbool.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum { WORD_SIZE = 63, BASE = 10, NONTYPABLE_CH = 127, NONTYPABLE = 31 };

int main(int argc, char *argv[]) {
    FILE *file;
    int buff;
    int max_int = 0;
    double min_double = INFINITY;
    bool int_flag = false;
    bool double_flag = false;
    char word[WORD_SIZE + 1];
    for (int i = 0; i < WORD_SIZE; ++i) {
        word[i] = 'a';
    }
    int dot_counter = 0;
    char *trash = NULL;
    int word_size = 0;
    bool only_digit = true;
    bool stdin_flag = false;
    if (argc == 1) {
        file = stdin;
        stdin_flag = true;
    } else if (argc == 2) {
        file = fopen(argv[1], "r");
    } else {
        fprintf(stderr, "Слишком много аргументов\n");
        exit(1);
    }
    if (file && ferror(file) == 0) {
        while ((buff = fgetc(file)) != EOF && !feof(file)) {
            if ((buff != '\n' && buff != '\t' && buff != '\r' && buff != ' ') &&
                ((buff >= 0 && buff <= NONTYPABLE) || buff == NONTYPABLE_CH)) {
                fprintf(stderr, "Недопустимые символы\n");
                exit(1);
            } else if (buff == '\n' || buff == '\t' || buff == '\r' ||
                       buff == ' ') {
                if (only_digit) {
                    int res;
                    long tmp = strtol(word, &trash, BASE);
                    if ((word_size != 0) &&
                        !(__builtin_add_overflow(tmp, 0, &res)) &&
                        (res > max_int || !int_flag)) {
                        max_int = res;
                        int_flag = true;
                    }
                } else {
                    double res = strtod(word, &trash);
                    if ((res < min_double || isnan(res)) &&
                        !isnan(min_double)) {
                        min_double = res;
                    }
                    double_flag = true;
                }

                only_digit = true;
                for (int i = 0; i < WORD_SIZE; ++i) {
                    word[i] = 'a';
                }
                dot_counter = 0;
                word_size = 0;
            } else if (isdigit(buff) && word_size < WORD_SIZE) {
                word[word_size] = buff;
                ++word_size;
            } else if (buff == '.' && dot_counter == 0 &&
                       word_size < WORD_SIZE && word_size > 0) {
                only_digit = false;
                word[word_size] = buff;
                ++word_size;
                ++dot_counter;
            } else if ((buff == '+' || buff == '-') && word_size == 0) {
                word[word_size] = buff;
                ++word_size;
            } else {
                while ((buff != '\n' && buff != '\t' && buff != '\r' &&
                        buff != ' ') &&
                       buff != EOF) {
                    if (word_size >= WORD_SIZE) {
                        fprintf(stderr, "Слишком длинное слово\n");
                        exit(1);
                    } else if (((buff >= 0 && buff <= NONTYPABLE) ||
                                buff == NONTYPABLE_CH)) {
                        fprintf(stderr, "Недопустимые символы\n");
                        exit(1);
                    }
                    word[word_size] = buff;
                    ++word_size;
                    buff = fgetc(file);
                }

                if (isnan(strtod(word, &trash))) {
                    min_double = NAN;
                    double_flag = true;
                } else if (isinf(strtod(word, &trash))) {
                    if (double_flag && strtod(word, &trash) < min_double &&
                        !isnan(min_double)) {
                        min_double = strtod(word, &trash);
                    } else if (!double_flag) {
                        min_double = strtod(word, &trash);
                        double_flag = true;
                    }
                }

                only_digit = true;
                for (int i = 0; i < WORD_SIZE; ++i) {
                    word[i] = 'a';
                }
                dot_counter = 0;
                word_size = 0;
            }
        }
        if (only_digit) {
            int res;
            if ((word_size != 0) &&
                !(__builtin_add_overflow(strtol(word, &trash, BASE), 0,
                                         &res)) &&
                (res > max_int || !int_flag)) {
                max_int = res;
                int_flag = true;
            }
        } else {
            double res = strtod(word, &trash);
            if ((res < min_double || isnan(res)) && !isnan(min_double)) {
                min_double = res;
            }
            double_flag = true;
        }
    } else {
        fprintf(stderr, "Падает на чтении файла\n");
        exit(1);
    }
    if (!int_flag || !double_flag) {
        fprintf(stderr, "Не нашлось числа\n");
        exit(1);
    }
        printf("%d %.10g\n", max_int, min_double);
    if (!stdin_flag) {
        fclose(file);
    }
    return 0;
}