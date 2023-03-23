#include <stdio.h>
#include <stdlib.h>

typedef struct List
{
    int data;
    int counter;
    struct List *prev;
    struct List *next;
} List;

void free_list(List *cur_list) {
    while (cur_list != NULL) {
        List *cur_next= cur_list->next;
        free(cur_list);
        cur_list = cur_next;
    }
}

List * push(List *head, int number) {
    List *num_pos = head; 
    if (head->data == number) {
        head->counter += 1;
        return head;
    }
    while (num_pos != NULL) { // trying to find number
        if (num_pos->data != number) {
            num_pos = num_pos->next;
        } else { // number found
            List *n_prev = num_pos->prev;
            List *n_next = num_pos->next;
            if (n_prev != NULL) {
                n_prev->next = n_next;
            }
            if (n_next != NULL) {
                n_next->prev = n_prev;
            }
            num_pos->prev = NULL; // num_pos is head now
            num_pos->next = head;
            head->prev = num_pos;
            num_pos->counter += 1;
            return num_pos;
        }
    }
    List *new_list = calloc(1, sizeof(*new_list));
    if (new_list== NULL) { // error
        free_list(head);
        return NULL;
    }
    new_list->data = number;
    new_list->counter = 1;
    new_list->prev = NULL;
    new_list->next = head;
    head->prev = new_list;
    return new_list;
}

int main(void) {
    List *head = NULL;
    List *tail = NULL;
    int number;
    int is_first_number = 1;
    while (scanf("%d", &number) != EOF) {
        if (is_first_number == 1) {
            head = calloc(1, sizeof(*head));
            if (head == NULL) { // error
                exit(1);
            }
            head->data = number;
            head->counter = 1;
            head->prev = NULL;
            head->next = NULL;
            is_first_number = 0;
            continue;
        }
        head = push(head, number);
    }
    if (head == NULL) {
        return 0;
    }
    tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    while (tail->prev != NULL) {
        printf("%d %d\n", tail->data, tail->counter);
        tail = tail->prev;
    }
    printf("%d %d\n", head->data, head->counter);
    free_list(head);
    return 0;
}