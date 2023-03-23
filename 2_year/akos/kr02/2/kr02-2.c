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
	if (number < 0) {
		fprintf(f, "%s", "-");
		number = -number;
	}
	size_t k = 0;
	int64_t text[BUF_SIZE];
    while (number != 0) {
    	text[k++] = number % 7;
    	number /= 7;
    }
    int i;
    for (i = k - 1; i >= 0; --i) {
		fprintf(f, "%ld", text[i]);
    }
}