#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    int val1 = strtol(argv[1], NULL, 9);
    int val2 = strtol(argv[2], NULL, 9);
    int sum;
    if (__builtin_add_overflow(val1, val2, &sum)) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    if (val2 == 0 || (val1 == INT_MIN && val2 == -1)) {
         printf("1\n");
    } else {
        printf("0\n");
    }
    return 0;
}
