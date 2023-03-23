#include <stdlib.h>

struct data {
    int (*get_rank)(const struct data*);
    char secret[];
};

static int compar(const void *p1, const void *p2) {
    int rank1 = (*(const struct data**)p1)->get_rank(*(const struct data**)p1);
    int rank2 = (*(const struct data**)p2)->get_rank(*(const struct data**)p2);
    if (rank1 > rank2) {
        return 1;
    }
    if (rank1 < rank2) {
        return -1;
    }
    return 0;
}

void rank_sort(struct data* elements[], size_t size) {
    qsort(elements, size, sizeof(*elements), compar);
}