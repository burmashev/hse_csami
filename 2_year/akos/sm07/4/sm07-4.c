#include <stdint.h>
#include <inttypes.h>

int imull_overflow(int64_t a, int64_t b, int64_t *res) {
    uint64_t u_a = a;
    uint64_t u_b = b;
    uint64_t u_res = u_a * u_b;
    *res = u_res;
    if (a == 0 || b == 0) { // at least one is с
        return 0;
    }
    if ((a > 0 && b > 0) || (a < 0 && b < 0)) { // + + or - -
        if (b > 0 && a > INT64_MAX / b) {
            return 1;
        }
        if (b < 0 && a < INT64_MAX / b) {
            return 1;
        }
    }
    if ((a > 0 && b < 0) || (a < 0 && b > 0)) { // + - or - + 
        if (b > 0 && a < INT64_MIN / b) {
            return 1;
        }
        if (b < 0 && b < INT64_MIN / a) {
            return 1;
        }
    }
    return 0;
}