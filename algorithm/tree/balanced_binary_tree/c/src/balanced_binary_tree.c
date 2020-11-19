#include "balanced_binary_tree.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void balance(struct Node **root, struct Node *node);
void left_rotate(struct Node **root, struct Node *node);
void right_rotate(struct Node **root, struct Node *node);

struct Node *find(struct Node *root, int val);
struct Node *find_max(struct Node *root);
struct Node *find_min(struct Node *root);

int max(int a, int b);

int max(int a, int b) {
    return a > b ? a : b;
}

void left_rotate(struct Node **root, struct Node *node) {
    if (node == NULL || node->right == NULL) {
        return;
    }
    struct Node *parent = node->parent;
    struct Node *right = node->right;
    if (parent != NULL) {
        if (node == parent->left) {
            parent->left = right;
        } else {
            parent->right = right;
        }
    } else {
        *root = right;
    }
    right->parent = parent;

    node->right = right->left;
    if (right->left != NULL) {
        right->left->parent = node;
    }
    node->height = max(get_height(node->left), get_height(node->right)) + 1;

    right->left = node;
    node->parent = right;
    right->height = max(get_height(right->left), get_height(right->right)) + 1;
}

void right_rotate(struct Node **root, struct Node *node) {
    if (node == NULL || node->left == NULL) {
        return;
    }
    struct Node *parent = node->parent;
    struct Node *left = node->left;
    if (parent != NULL) {
        if (parent->left == node) {
            parent->left = left;
        } else {
            parent->right = left;
        }
    } else {
        *root = left;
    }
    left->parent = parent;

    node->left = left->right;
    if (left->right != NULL) {
        left->right->parent = node;
    }
    node->height = max(get_height(node->left), get_height(node->right)) + 1;

    left->right = node;
    node->parent = left;
    left->height = max(get_height(left->left), get_height(left->right)) + 1;
}

bool insert(struct Node **root, int val) {
    //printf("line %d, insert %d\n", __LINE__, val);
    if (root == NULL) {
        return false;
    }
    struct Node *cur = *root;
    struct Node *parent = NULL;
    while (cur != NULL) {
        if (cur->val == val) {
            return false;
        }
        parent = cur;
        if (cur->val > val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    node->val = val;
    node->height = 0;
    if (parent == NULL) {
        *root = node;
        return true;
    }
    if (parent->val > val) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    node->parent = parent;
    balance(root, node);
    return true;
}

void balance(struct Node **root, struct Node *node) {
    while (node != NULL && node->parent != NULL) {
        node = node->parent;
        int fac = get_factor(node);
        if (abs(fac) <= 1) {
            int h_child = max(get_height(node->left), get_height(node->right));
            if (h_child + 1 == node->height) {
                return;
            }
            node->height = max(get_height(node->left), 
                    get_height(node->right)) + 1;
            continue;
        }
        if (fac > 1) {
            int fac_left = get_factor(node->left);
            if (fac_left < 0) { // LR
                left_rotate(root, node->left);
            }
            right_rotate(root, node);
        } else{
            int fac_right = get_factor(node->right);
            if (fac_right > 0) { // RL
                right_rotate(root, node->right);
            }
            left_rotate(root, node);
        }
    }
}

bool delete(struct Node **root, int val) {
    struct Node *node = find(*root, val);
    if (node == NULL) {
        return false;
    }
    struct Node *replace = find_max(node->left);
    if (replace == NULL) {
        replace = find_min(node->right);
    }
    if (replace == NULL) { // 叶子节点
        if (node->parent == NULL) { // 根节点
            free(node);
            *root = NULL;
            return true;
        }
        if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
        balance(root, node);
        free(node);
        return true;
    }
    if (replace->val > val) { // 后继
        if (replace == replace->parent->left) {
            replace->parent->left = replace->right;
        } else {
            replace->parent->right = replace->right;
        }
        if (replace->right != NULL) {
            replace->right->parent = replace->parent;
        }
    } else { // 前驱
        if (replace == replace->parent->left) {
            replace->parent->left = replace->left;
        } else {
            replace->parent->right = replace->left;
        }
        if (replace->left != NULL) {
            replace->left->parent = replace->parent;
        }
    }
    node->val = replace->val;
    balance(root, replace);
    free(replace);
    return true;
}

struct Node *find(struct Node *root, int val) {
    while (root != NULL) {
        if (root->val == val) {
            return root;
        }
        if (root->val > val) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return NULL;
}

struct Node *find_max(struct Node *root) {
    while (root != NULL && root->right != NULL) {
        root = root->right;
    }
    return root;
}

struct Node *find_min(struct Node *root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}
