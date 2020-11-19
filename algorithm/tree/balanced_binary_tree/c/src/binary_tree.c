#include "binary_tree.h"
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct List {
    struct Node *node;
    struct List *next;
};

void push(struct List **list, struct Node *node);
struct Node* pop(struct List **list);
bool empty(struct List **list);

void inorder_visit(struct Node *root) {
    struct List *list = NULL;
    while (root != NULL || !empty(&list)) {
        while (root != NULL) {
            push(&list, root);
            root = root->left;
        }
        root = pop(&list);
        printf("%d ", root->val);
        root = root->right;
    }
    printf("\n");
}

void push(struct List **list, struct Node *node) {
    if (list == NULL) {
        return;
    }
    struct List *tmp = (struct List*) malloc(sizeof(struct List));
    tmp->node = node;
    tmp->next = *list;
    *list = tmp;
}

struct Node* pop(struct List **list) {
    if (list == NULL || *list == NULL) {
        return NULL;
    }
    struct List *tmp = *list;
    struct Node *node = tmp->node;
    (*list) = (*list)->next;
    free(tmp);
    return node;
}

bool empty(struct List **list) {
    if (list == NULL || *list == NULL) {
        return true;
    }
    return false;
}
