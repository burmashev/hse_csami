#include <stdio.h>

int bitcount(STYPE value) {
    int answer = 0;
    UTYPE uvalue = (UTYPE)value;
    while (uvalue != 0) {
        answer += uvalue & 1;
        uvalue >>= 1;
    }
    return answer;
}
