#include <stdint.h>
#include <cstdio>

uint32_t satsum(uint32_t v1, uint32_t v2) {
uint32_t v3 = v1;
v1 += v2;
if (v1 < v3) {
return -1;
} else {
return v1;
}


int main() {
	uint32_t a = 10;
	uint32_t b = 0;
	uint32_t c = satsum(a, b);
	printf("%u", c);
}