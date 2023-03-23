#include <inttypes.h>
#include <stdio.h>

enum { EXP = 5, MANT = 10 };

uint16_t sat_mul4_half(uint16_t f) {
	typedef union {
       	uint16_t u;
        float f;
    } ufloat;
    float num = f;
    ufloat uf;
    uf.f = num;
    uint16_t exp = (uf.u >> MANT) & ((1 << EXP) - 1);
     if (exp == 0xff) {
        return f;
    }
    if (exp == 0) {
        return 4 * f;
    }
    return UINT16_MAX;
}
