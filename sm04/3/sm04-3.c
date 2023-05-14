int mystrcmp(const char *str1, const char *str2) {
    unsigned char *first = (unsigned char *)str1;
    unsigned char *second = (unsigned char *)str2;
    while (*first != '\0' && *second != '\0') {
        if (*first < *second) {
            return -1;
        } else if (*first > *second) {
            return 1;
        }
        ++first;
        ++second;
    }
    if (*second == '\0' && *first != '\0') {
        return 1;
    } else if (*first == '\0' && *second != '\0') {
        return -1;
    }

    return 0;
}
