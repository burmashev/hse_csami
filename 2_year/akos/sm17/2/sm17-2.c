#include <stdio.h>
#include <pthread.h>
#include <stdint.h>

void *thread_func(void* arg) {
	int n;
	if (scanf("%d", &n) == EOF) {
		return NULL;
	}
	pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);
    printf("%d\n", n);
	return NULL;
};

int main(void) {
	pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);
	return 0;
}