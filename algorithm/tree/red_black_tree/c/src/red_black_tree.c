#include "red_black_tree.h"
#include <stddef.h>
#include <stdlib.h>

static struct Node* find(struct Node *root, int val);
static struct Node* findMax(struct Node *root);
static struct Node* findMin(struct Node *root);
static void insert_balance(struct Node **root, struct Node *node);
static void delete_balance(struct Node **root, struct Node *node);
static void left_rotate(struct Node **root, struct Node *node);
static void right_rotate(struct Node **root, struct Node *node);

bool insert(struct Node **root, int val) {
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
    node->color = red;
    node->val = val;
    if (parent == NULL) {
        node->color = black;
        *root = node;
        return true;
    }
    if (parent->val > val) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    node->parent = parent;
    insert_balance(root, node);
    return true;
}

bool delete(struct Node **root, int val) {
    struct Node *node = find(*root, val);
    if (node == NULL) {
        return false;
    }
    struct Node *replace = findMax((*root)->left);
    if (replace == NULL) {
        replace = findMin((*root)->right);
    }
    if (replace == NULL) { // 叶子节点
        if (node->parent == NULL) {
            *root = NULL;
            free(node);
            return true;
        }
        if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
        if (node->color == black) {
            delete_balance(root, node);
        }
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
    } else {
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
    if (replace->color == black) {
        delete_balance(root, replace);
    }
    free(replace);
    return true;
}

static void insert_balance(struct Node **root, struct Node *node) {
    while (node != NULL) {
        struct Node *parent = node->parent;
        // case 1
        if (get_color(parent) == black) {
            if (parent == NULL) {
                node->color = black;
            }
            return;
        }
        struct Node *grandp = parent->parent;
        struct Node *uncle = NULL;
        if (parent == grandp->left) {
            uncle = grandp->right;
        } else {
            uncle = grandp->left;
        }
        // case 2
        if (get_color(uncle) == red) {
            parent->color = black;
            uncle->color = black;
            grandp->color = red;
            node = grandp;
            continue;
        }
        // case 3
        grandp->color = red;
        if (parent == grandp->left) {
            if (node == parent->right) {
                left_rotate(root, parent);
                parent = parent->parent;
            }
            parent->color = black;
            right_rotate(root, grandp);
            return;
        }
        // case 4
        if (node == parent->left) {
            right_rotate(root, parent);
            parent = parent->parent; // here paren become child
        }
        parent->color = black;
        left_rotate(root, grandp);
        return;
    }
}

static void delete_balance(struct Node **root, struct Node *node) {
    // case 2

}

static void left_rotate(struct Node **root, struct Node *node) {
    if (node == NULL || node->right == NULL) {
        return;
    }
    struct Node *parent = node->parent;
    struct Node *right = node->right;
    if (parent == NULL) {
        *root = right;
    } else if (node == parent->left) {
        parent->left = right;
    } else {
        parent->right = right;
    }
    right->parent = parent;

    node->right = right->left;
    if (node->right != NULL) {
        node->right->parent = node;
    }

    right->left = node;
    node->parent = right;
}

static void right_rotate(struct Node **root, struct Node *node) {
    if (node == NULL || node->left == NULL) {
        return;
    }
    struct Node *parent = node->parent;
    struct Node *left = node->left;
    if (parent == NULL) {
        *root = left;
    } else if (node == parent->left) {
        parent->left = left;
    } else {
        parent->right = left;
    }
    left->parent = parent;

    node->left = left->right;
    if (node->left != NULL) {
        node->left->parent = node;
    }

    left->right = node;
    node->parent = left;
}

static struct Node* find(struct Node *root, int val) {
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

static struct Node* findMax(struct Node *root) {
    while (root != NULL || root->right != NULL) {
        root = root->right;
    }
    return root;
}

static struct Node* findMin(struct Node *root) {
    while (root != NULL || root->left != NULL) {
        root = root->left;
    }
    return root;
}
