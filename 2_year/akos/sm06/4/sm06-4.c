#include <stdio.h>
#include <stdlib.h>

struct List {
        int v;
        struct List *next;
};

int main() {
        int num;
        struct List* list = NULL;

        while (scanf("%d", &num) != EOF) {
                struct List *new_list = calloc(1, sizeof(*new_list));
                new_list->v = num;
                new_list->next = list;
                list = new_list;
        }
        while (list != NULL) {
                struct List* last = list->next;
                printf("%d\n", list->v);
                free(list);
                list = last;
        }
        return 0;
}

/*#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int data;
    struct List *prev;
} List;

void free_list(List *cur_list) {
    while (cur_list != NULL) {
        List *cur_prev = cur_list->prev;
        free(cur_list);
        cur_list = cur_prev;
    }
}

int main() {
    List *list = NULL;
    List *list_to_print = NULL;
    int number;
    while (scanf("%d", &number) != EOF) {
        List *new_list = calloc(1, sizeof(*new_list));
        if (new_list == NULL) { // error
            free_list(list);
            return 1;
        }
        new_list->data = number;
        new_list->prev = list;
        list = new_list;
    }
    list_to_print = list;
    while (list_to_print != NULL) {
        printf("%d\n", list_to_print->data);
        list_to_print = list_to_print->prev;
    }
    free_list(list);
    return 0;
}
*/