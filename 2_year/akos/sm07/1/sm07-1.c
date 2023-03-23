#include <stdio.h>
#include <stdint.h>

int32_t satsum(int32_t v1, int32_t v2) { 
	int32_t answer;
	if (__builtin_add_overflow(v1, v2, &answer)) {
		uint32_t overflow = -1u >> 1;
		if (v1 < 0 && v2 < 0) {
			return ~overflow;
		}
		return overflow;
	}
	return answer;
}