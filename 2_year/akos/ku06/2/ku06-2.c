#include <stdint.h>

enum { EXP = 8, MANT = 23 };

void myfloorf(float *arg) {
    if (arg == 0) {
        return;
    }
    typedef union {
        unsigned u;
        float f;
    } ufloat;
    ufloat uf;
    uf.f = *arg;
    unsigned exp = (uf.u >> MANT) & ((1 << EXP) - 1);
    if (exp < 127) { 
        *arg = 0.0;
        return;
    };
    if (exp - 127 >= MANT) {
        return;
    }
    exp -= 127;
    uf.u >>= MANT - exp;
    uf.u <<= MANT - exp;
    *arg = uf.f;
    return;
}