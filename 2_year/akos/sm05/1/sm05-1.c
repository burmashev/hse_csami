void normalize_path(char *buf) {
    char *first = buf;
    char *second = buf;
    while (*second != 0) {
        if (*second == '/') {
            while (*first == '/') {
                first++;
            }
        } else {
            first++;
        }
        second++;
        *second = *first;
    }
};

