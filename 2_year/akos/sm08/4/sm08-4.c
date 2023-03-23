#include <stdlib.h>

struct data {
    int (*get_rank)(const struct data*);
    char secret[];
};

static int compar(const struct data **p1, const struct data **p2) {
    int rank1 = (*p1)->get_rank(*p1);
    int rank2 = (*p2)->get_rank(*p2);
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