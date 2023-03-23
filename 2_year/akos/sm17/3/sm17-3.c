#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

enum { N = 3, ITER = 1000000  };

pthread_t ids[N];
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

volatile double nums[N];

void *thread_func(void* arg) {
	int i = (int)(intptr_t)arg;
	if (i == 0) {
		for (int j = 0; j != ITER; ++j) {
			pthread_mutex_lock(&counter_mutex);
			nums[0] += 100;
			nums[1] -= 101;
			pthread_mutex_unlock(&counter_mutex);
		}
	}
	if (i == 1) {
		for (int j = 0; j != ITER; ++j) {
			pthread_mutex_lock(&counter_mutex);
			nums[1] += 200;
			nums[2] -= 201;
			pthread_mutex_unlock(&counter_mutex);
		}
	}
	if (i == 2) {
		for (int j = 0; j != ITER; ++j) {
			pthread_mutex_lock(&counter_mutex);
			nums[2] += 300;
			nums[0] -= 301;
			pthread_mutex_unlock(&counter_mutex);
		}
	}
	return NULL;
};

int main(void) {
	pthread_create(&ids[0], NULL, thread_func, (void*)(intptr_t)0);
	pthread_create(&ids[1], NULL, thread_func, (void*)(intptr_t)1);
	pthread_create(&ids[2], NULL, thread_func, (void*)(intptr_t)2);

	pthread_join(ids[0], NULL);
	pthread_join(ids[1], NULL);
	pthread_join(ids[2], NULL);

	printf("%.10g\n", nums[0]);
	printf("%.10g\n", nums[1]);
	printf("%.10g\n", nums[2]);
	return 0;
}
