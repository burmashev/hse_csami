#include <stdio.h>

void dot_product(int, const float *, const float *, float *r);

int main() {
	float a[3] = {1, 2, 3};
	float b[3] = {1, 2, 3};
	float result;
	dot_product(3, a, b, &result);
	printf("%f\n", result);

}