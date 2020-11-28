#include "red_black_tree.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

static struct Node* find(struct Node *root, int val);
static struct Node* find_max(struct Node *root);
static struct Node* find_min(struct Node *root);
static void insert_balance(struct Node **root, struct Node *node);
static void delete_balance(struct Node **root, struct Node *node, bool flag);
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
    struct Node *replace = find_max(node->left);
    if (replace == NULL) {
        replace = find_min(node->right);
    }
    bool flag;
    if (replace == NULL) { // 叶子节点
        if (node->parent == NULL) {
            *root = NULL;
            free(node);
            return true;
        }
        if (node == node->parent->left) {
            node->parent->left = NULL;
            flag = true;
        } else {
            node->parent->right = NULL;
            flag = false;
        }
        delete_balance(root, node, flag);
        free(node);
        return true;
    }
    if (replace->val > val) { // 后继
        if (replace == replace->parent->left) {
            replace->parent->left = replace->right;
            flag = true;
        } else {
            replace->parent->right = replace->right;
            flag = false;
        }
        if (replace->right != NULL) {
            replace->right->parent = replace->parent;
        }
    } else {
        if (replace == replace->parent->left) {
            replace->parent->left = replace->left;
            flag = true;
        } else {
            replace->parent->right = replace->left;
            flag = false;
        }
        if (replace->left != NULL) {
            replace->left->parent = replace->parent;
        }
    }
    //printf("%s line:%d\n", __func__, __LINE__);
    node->val = replace->val;
    delete_balance(root, replace, flag);
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

// flag == true 表示被删除节点是其父节点的左子树根节点
static void delete_balance(struct Node **root, struct Node *node, bool flag) {
    while (node != NULL && node->parent != NULL && node->color == black) {
        struct Node *p = node->parent;
        struct Node *w = NULL;
        if (flag) {
            w = p->right;
            if (get_color(w) == red) {
                w->color = black;
                p->color = red;
                left_rotate(root, p);
                w = p->right;
            }
            if (get_color(w->left) == black && get_color(w->right) == black) {
                w->color = red;
                node = p;
            } else {
                if (get_color(w->right) == black) {
                    w->left->color = black;
                    w->color = red;
                    right_rotate(root, w);
                    w = p->right;
                }
                w->color = p->color;
                p->color = black;
                w->right->color = black;
                left_rotate(root, p);
                node = *root;
                continue;
            }
            if (node->parent != NULL) {
                flag = node == node->parent->left;
            }
            continue;
        } 
        w = p->left;
        if (get_color(w) == red) {
            w->color = black;
            p->color = red;
            right_rotate(root, p);
            w = p->left;
        }
        if (get_color(w->left) == black && get_color(w->right) == black) {
            w->color = red;
            node = p;
        } else {
            if (get_color(w->left) == black) {
                w->right->color = black;
                w->color = red;
                left_rotate(root, w);
                w = p->left;
            }
            w->color = p->color;
            p->color = black;
            w->left->color = black;
            right_rotate(root, p);
            node = *root;
            continue;
        }
        if (node->parent != NULL) {
            flag = node == node->parent->left;
        }
    }
    node->color = black;
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

static struct Node* find_max(struct Node *root) {
    while (root != NULL && root->right != NULL) {
        root = root->right;
    }
    return root;
}

static struct Node* find_min(struct Node *root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}
