#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
    int data;
    struct Tree *left;
    struct Tree *right; 
} Tree;

void print_tree(Tree* cur_tree) {
    if (cur_tree->right != NULL) {
        print_tree(cur_tree->right);
    }
    printf("%d ", cur_tree->data);
    if (cur_tree->left != NULL) {
        print_tree(cur_tree->left);
    }
}

void free_tree(Tree *cur_tree) {
    if (cur_tree == NULL) {
        return;
    }
    if (cur_tree->right != NULL) {
        free_tree(cur_tree->right);
    }
    if (cur_tree->left != NULL) {
        free_tree(cur_tree->left);
    }
    free(cur_tree);
}

Tree * push(Tree *cur_tree, int number) {
    Tree *num_pos = cur_tree;
    Tree *parent = NULL;
    if (num_pos->data == number) {
        return cur_tree;
    }
    while (num_pos != NULL) {
        if (num_pos->data == number) {
            return cur_tree;
        } 
        parent = num_pos;
        if (num_pos->data < number) {
            num_pos = num_pos->right;
        } else if (num_pos->data > number) {
            num_pos = num_pos->left;
        }
    }
    Tree *new_tree = calloc(1, sizeof((*new_tree)));
    if (new_tree == NULL) { // error
        free_tree(cur_tree);
        return NULL;
    }
    new_tree->data = number;
    new_tree->left = NULL;
    new_tree->right = NULL;
    if (parent->data < number) {
        parent->right = new_tree;
    } else if (parent->data > number) {
        parent->left = new_tree;
    }
    return cur_tree;
}

int main(void) {
    Tree *tree = NULL;
    int number = 0;
    int is_first_number = 1; 
    while (scanf("%d", &number) != EOF) {
        if (number != 0) {
            if (is_first_number == 1) {
                Tree *new_tree = calloc(1, sizeof(*new_tree));
                if (new_tree == NULL) { // error
                    exit(1);
                }
                new_tree->data = number;
                new_tree->left = NULL;
                new_tree->right = NULL;
                tree = new_tree;
                is_first_number = 0;
                continue;
            }
            tree = push(tree, number);
        } else {
            if (tree != NULL) {
                print_tree(tree);
                Tree *cur_tree = tree;
                free_tree(cur_tree);
            }
            printf("%s ", "0");
            tree = NULL;
            is_first_number = 1;
        }
    }
    if (tree != NULL) {
        print_tree(tree);
        printf("%s", "0");
        free_tree(tree);
    }
    printf("\n");
    return 0;
}