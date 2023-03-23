#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

enum { N = 10 };

pthread_t ids[N];

void *thread_func(void* arg) {
	int i = (int)(intptr_t)arg;
	if (i > 0) {
		pthread_join(ids[i - 1], NULL);
	}
	printf("%d\n", i);
	return NULL;
};

int main(void) {
	for (int i = 0; i != N; ++i) {
		pthread_create(&ids[i], NULL, thread_func, (void*)(intptr_t)i);
	}
	pthread_join(ids[N - 1], NULL);
	return 0;
}