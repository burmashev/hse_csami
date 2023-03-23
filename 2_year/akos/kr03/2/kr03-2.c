#include <stdio.h>
#include <stdint.h>

uint64_t rdtsc() {
	uint32_t a, d;
	asm ( 
		"rdtsc"
		: "=a"(a), "=d"(d)
		: /* No input */			
		: /* No clobbers */
	);
	uint64_t ans = 1;
	ans = (ans^d)<<(sizeof(a)*8);
    ans = ans^a;
	return ans;
}

void work_until_deadline(const uint64_t *deadline, void (*do_work)()) {
	while (rdtsc() < *deadline) {
		do_work();
	}
}