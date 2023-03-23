#include <stdio.h>
#include <stdlib.h>

static void destroy(void *random_generator);

static int next(void *random_generator);

enum 
{
    MULTIPLICATOR = 1103515245u,
    INCREMENT = 12345u,
    MOD = (1u << 31)
};

typedef struct RandomOperations 
{
    void (*destroy)(void *random_generator);
    int (*next)(void *random_generator);
} RandomOperations;

const RandomOperations R_ops = { &destroy, &next };

typedef struct RandomGenerator
{
    unsigned int seed;
    const RandomOperations *ops;
} RandomGenerator;

void destroy(void *random_generator) {
    free(random_generator);
}

int next(void *random_generator) {
    RandomGenerator *rr = random_generator;
    rr->seed = (MULTIPLICATOR * rr->seed + INCREMENT) % MOD;
    return rr->seed;
}

RandomGenerator *random_create(int seed) {
    RandomGenerator *rr = calloc(1, sizeof(*rr));
    if (rr == NULL) { // error
        free(rr);
        return NULL;
    }
    rr->seed = seed;
    rr->ops = &R_ops;
    return rr;
}