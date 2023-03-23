#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

enum {
	BUF_SIZE = 1000
};

void fprint7(FILE* f, int64_t number) {
	if (number == 0) {
		fprintf(f, "%d", 0);
		return;
	}
	int is_negative = 0;
	if (number < 0) {
		fprintf(f, "%s", "-");
		is_negative = 1;
	}
	size_t k = 0;
	int64_t text[BUF_SIZE];
    while (number != 0) {
    	int cur_num = number % 7;
    	if (is_negative == 1) {
    		cur_num = -cur_num;
    	}
    	text[k++] = cur_num;
    	number /= 7;
    }
    for (int i = k - 1; i >= 0; --i) {
		fprintf(f, "%ld", text[i]);
    }
}