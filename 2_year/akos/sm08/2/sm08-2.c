#include <stdio.h>

enum { EXP = 8, MANT = 23 };

int main(void) {
    typedef union {
        unsigned u;
        float f;
    } ufloat;
    float num;
    while (scanf("%f", &num) == 1) {
        ufloat uf;
        uf.f = num;
        unsigned sgn = uf.u >> 31;
        unsigned exp = (uf.u >> MANT) & ((1 << EXP) - 1);
        unsigned mant = uf.u & ((1 << MANT) - 1);
        printf("%u %u %x\n", sgn, exp, mant);
    }   
    return 0;
}