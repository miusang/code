#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

struct List {
    struct Node *node;
    struct List *next;
};

void push(struct List **list, struct Node *node) {
    struct List *p = (struct List*) malloc(sizeof(struct List));
    p->node = node;
    p->next = *list;
    *list = p;
}

struct Node* pop(struct List **list) {
    if (list == NULL || *list == NULL) {
        return NULL;
    }
    struct Node *top = (*list)->node;
    struct List *tmp = *list;
    *list = (*list)->next;
    free(tmp);
    return top;
}

int empty(struct List **list) {
    if (list == NULL || *list == NULL) {
        return 1;
    }
    return 0;
}
void preorder_visit(struct Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preorder_visit(root->left);
    preorder_visit(root->right);
}

// 二叉搜索树中序遍历是一个有序序列
/*
void inorder_visit(struct Node *root) {
    if (root == NULL) {
        return;
    }
    inorder_visit(root->left);
    printf("%d ", root->val);
    inorder_visit(root->right);
}*/
void inorder_visit(struct Node *root) {
    struct List *list = NULL;
    struct Node *cur = root;
    while (cur != NULL || empty(&list) != 1) {
        if (cur != NULL) {
            push(&list, cur);
            cur = cur->left;
            continue;
        }
        cur = pop(&list);
        printf("%d ", cur->val);
        cur = cur->right;
    }
    printf("\n");
}
