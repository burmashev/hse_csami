#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <inttypes.h>

volatile bool f;
volatile uint64_t cur_num;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// used 
// https://stackoverflow.com/questions/4424374/determining-if-a-number-is-prime

bool is_prime(uint64_t num) {
    if (num < 2) {
        return false;
    }
    if (num == 2) {
        return true;
    }
    if (num % 2 == 0) {
        return false;
    }
    for (uint64_t i = 3; i * i <= num; i+=2) { // sqrt check
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void *thread_func(void* arg) {
    uint64_t i = *(uint64_t *)arg;
    while (1) {
        if (is_prime(i)) {
            pthread_mutex_lock(&mutex);
            cur_num = i;
            f = true;
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&mutex);
        }
        ++i;
    }
    return NULL;
}

int main(void) {
    uint64_t base;
    uint64_t prime;
    int32_t count;
    if (scanf("%" SCNu64 " %" SCNd32, &base, &count) == EOF) {
        return 1;
    };
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, &base);    
    for (int i = 0; i != count; ++i) {
        pthread_mutex_lock(&mutex);
        while (!f) {
            pthread_cond_wait(&cond, &mutex);
        }
        f = false;
        prime = cur_num;
        printf("%" PRIu64 "\n", prime);
        pthread_mutex_unlock(&mutex);
    }
    return 0;
}