#include <stdio.h>

int main(void) {
	unsigned a, c, d;
	unsigned family, model;
	asm ( 
		"cpuid"
		: "=a"(a), "=c"(c), "=d"(d)
		: "a"(1)			
		: "ebx"
	);
	unsigned model_id = (a << 24) >> 28;
	unsigned ext_model_id = (a << 12) >> 28;
	unsigned family_id = (a << 20) >> 28;
	unsigned ext_family_id = (a << 4) >> 24;
	if (family_id == 6 || family_id == 15) {
		ext_model_id <<= 4;
		model = model_id + ext_model_id;
	} else {
		model = model_id;
	}
	if (family_id == 15) {
		family = family_id + ext_family_id;
	} else {
		family = family_id;
	}
	printf("%s%d ", "family=", family);
	printf("%s%d ", "model=", model);
	printf("%s0x%x ", "ecx=", c);
	printf("%s0x%x", "edx=", d);
}