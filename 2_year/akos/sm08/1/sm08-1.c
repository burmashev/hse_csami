#include <stdio.h>

enum { EXP = 8, MANT = 23 };

FPClass fpclassf(float value, int *psign) {
    typedef union {
        unsigned u;
        float f;
    } ufloat;
    ufloat uf;
    uf.f = value;
    unsigned sgn = uf.u >> 31;
    unsigned exp = (uf.u >> MANT) & ((1 << EXP) - 1);
    unsigned mant = uf.u & ((1 << MANT) - 1);
    *psign = sgn;
    if (exp == 0xff) {
        if (mant == 0) {
            return FFP_INF;
        }
        *psign = 0;
        return FFP_NAN;
    }
    if (exp == 0) {
        if (mant == 0) {
            return FFP_ZERO;
        }
        return FFP_DENORMALIZED;
    }
    return FFP_NORMALIZED;
}