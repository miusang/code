#include "binary_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct NodeLink {
    struct Node* node;
    struct NodeLink *next;
};

bool empty(struct NodeLink *list);
void push(struct NodeLink **list, struct Node *node);
void push_back(struct NodeLink **list, struct Node *node);
struct Node* pop(struct NodeLink **list);

void inorder_visit(struct Node *root) {
    struct NodeLink *list = NULL;
    while (root != NULL || !empty(list)) {
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

void level_visit(struct Node *root) {
    if (root == NULL) {
        return;
    }
    struct NodeLink *list = NULL;
    push_back(&list, root);
    while (!empty(list)) {
        root = pop(&list);
        printf("%d(%d) ", root->val, root->color == black);
        if (root->left != NULL) {
            push_back(&list, root->left);
        }
        if (root->right != NULL) {
            push_back(&list, root->right);
        }
    }
    printf ("\n");
}

bool empty(struct NodeLink *list) {
    return list == NULL;
}

void push(struct NodeLink **list, struct Node *node) {
    struct NodeLink *item = (struct NodeLink*) malloc(sizeof(struct NodeLink));
    item->node = node;
    item->next = *list;
    *list = item;
}

void push_back(struct NodeLink **list, struct Node *node) {
    struct NodeLink *item = (struct NodeLink*) malloc(sizeof(struct NodeLink));
    item->node = node;
    struct NodeLink *cur = *list;
    while (cur != NULL && cur->next != NULL) {
        cur = cur->next;
    }
    if (cur == NULL) {
        *list = item;
        return;
    }
    cur->next = item;
}

struct Node* pop(struct NodeLink **list) {
    if (list == NULL || *list == NULL) {
        return NULL;
    }
    struct NodeLink *item = *list;
    struct Node* node = item->node;
    *list = (*list)->next;
    free(item);
    return node;
}
