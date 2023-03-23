#include <stdio.h>
#include <stdlib.h>

char *getline2(FILE *f) {
    if (f == NULL) { // empty 
        return NULL;
    }
    size_t capacity = 1;
    char *for_realloc = NULL;
    char *text = calloc(capacity, sizeof(*text));
    if (text == NULL) { // error
        return NULL;
    }
    char c;
    size_t size = 0;
    text[size] = '\0';
    while (fscanf(f, "%c", &c) != EOF) {
        text[size++] = c;
        if (capacity == size) {
            capacity *= 2;
            for_realloc = realloc(text, capacity * sizeof(*text));
            if (for_realloc == NULL) { // error 
                free(text);
                return NULL;
            }
            text = for_realloc;
        }
        text[size] = '\0';
        if (c == '\n') {
            break;
        }
    }
    if (size == 0) {
        free(text);
        return NULL;
    }
    return text;
}