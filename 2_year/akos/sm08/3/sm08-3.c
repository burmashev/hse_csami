#include <stdio.h>
#include <stdint.h>

int check(unsigned num) {
    int first = -1;
    int second = -1;
    int found_first = 0;
    int position = 1;
    while (position <= 32 && num > 0) {
        if (num % 2 == 1) {
            if (found_first == 0) {
                first = position;
                found_first = 1;
            }
            second = position;
        }
        ++position;
        num >>= 1;
    }
    if (second <= 24) {
        return 1;
    } else {
        if (second - first < 24) {
            return 1;
        }
        return 0;
    }
}

int main(void) {
    unsigned num;
    while (scanf("%u", &num) == 1) {
        printf("%d\n", check(num));
    }
    return 0;
}
