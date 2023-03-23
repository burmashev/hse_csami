#include <stdio.h>

int main() {
	unsigned int a, b, answer;
	scanf("%u %u", &a, &b);
	answer = a / 2 + b / 2;
	if (a % 2 == 1 && b % 2 == 1) {
		++answer;
	}
	printf("%u\n", answer);
	return 0;
}
