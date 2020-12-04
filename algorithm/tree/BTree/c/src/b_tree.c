#include "b_tree.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static void insert_fix(struct Node **root, struct Node *node);
static void erase_fix(struct Node **root, struct Node *node);
static struct Node* find(struct Node *root, int val);
static struct Node* find_max(struct Node *node);
static struct Node* find_min(struct Node *node);

void insert(struct Node **root, int val) {
    struct Node *cur = *root;
    struct Node *parent = NULL;
    while (cur != NULL) {
        int i = 0;
        for (; i < cur->len; i++) {
            if (val < cur->vals[i]) {
                break;
            }
        }
        parent = cur;
        cur = cur->childs[i];
    }
    if (parent == NULL) {
        *root = new_node();
        insert_elem(*root, val);
        return;
    }
    insert_elem(parent, val);
    insert_fix(root, parent);
}

int erase(struct Node **root, int val) {
    struct Node *node = find(*root, val);
    if (node == NULL) {
        return -1;
    }
    int index = index_of_elem(node, val);
    struct Node *replace = find_max(node->childs[index]);
    if (replace == NULL) {
        replace = find_min(node->childs[index + 1]);
    }
    if (replace == NULL) { // 叶子节点
        remove_elem(node, val);
        erase_fix(root, node);
        return 0;
    }
    int replace_val;
    if (replace->vals[0] >= val) {
        replace_val = replace->vals[0];
    } else {
        replace_val = replace->vals[replace->len - 1];
    }
    node->vals[index] = replace_val;
    remove_elem(replace, replace_val);
    erase_fix(root, replace);
}

void inorder_visit(struct Node *root) {
    if (root == NULL) {
        return;
    }
    int i = 0;
    for (; i < root->len; i++) {
        inorder_visit(root->childs[i]);
        printf("%d ", root->vals[i]);
    }
    inorder_visit(root->childs[i]);
}

static void insert_fix(struct Node **root, struct Node *node) {
    while (node->len >= TREE_M) {
        int mid = TREE_M / 2;
        int val = node->vals[mid];
        struct Node *node2 = new_node();
        for (int i = mid + 1; i < TREE_M; i++) {
            insert_elem(node2, node->vals[i]);
        }
        node->len = mid;
        for (int i = mid + 1; i < TREE_M + 1; i++) {
            node2->childs[i - mid - 1] = node->childs[i];
            if (node->childs[i] != NULL) {
                node->childs[i]->parent = node2;
                node->childs[i] = NULL;
            }
        }

        if (node->parent == NULL) {
            *root = new_node();
            node->parent = *root;
            insert_child(node->parent, node, 0);
        }
        int index = insert_elem(node->parent, val);
        insert_child(node->parent, node2, index + 1);
        node2->parent = node->parent;
        node = node->parent;
        //printf("%s line %d\n", __func__, __LINE__);
    }
}

static void erase_fix(struct Node **root, struct Node *node) {
    while (node != NULL && node->len < TREE_M / 2) {
        printf("%s line %d\n", __func__, __LINE__);
        if (node->parent == NULL) {
            if (node->len == 0) {
                free(node);
                *root = NULL;
            }
            return;
        }
        struct Node *parent = node->parent;
        int index, brother_index;
        for (int i = 0; i < parent->len + 1; i++) {
            if (node == parent->childs[i]) {
                index = i;
            } else {
                brother_index= i;
            }
        }
        printf("%s line %d\n", __func__, __LINE__);
        struct Node *brother = parent->childs[brother_index];
        if (brother->len > TREE_M / 2) {
            int val_up, val_down;
            if (node->vals[0] >= brother->vals[brother->len - 1]) {
                val_down = parent->vals[index - 1];
                val_up = brother->vals[brother->len - 1];
                brother->childs[brother->len-1] = brother->childs[brother->len];
                brother->childs[brother->len] = NULL;
            } else {
                val_down = parent->vals[index];
                val_up = brother->vals[0];
                for (int i = 0; i < brother->len; i++) {
                    brother->childs[i] = brother->childs[i + 1];
                }
                brother->childs[brother->len] = NULL;
            }
            remove_elem(brother, val_up);
            insert_elem(node, val_down);
            return;
        }
        printf("%s line %d\n", __func__, __LINE__);
        int val_down;
        if (node->vals[0] >= brother->vals[brother->len - 1]) {
            printf("%s line %d\n", __func__, __LINE__);
            val_down = parent->vals[index - 1];
            insert_elem(brother, val_down);
            for (int i = 0; node->len; i++) {
                brother->childs[brother->len] = node->childs[i];
                insert_elem(brother, node->vals[i]);
            }
            brother->childs[brother->len] = node->childs[node->len];
            for (int i = index - 1; i < parent->len + 1; i++) {
                parent->childs[i] = parent->childs[i+1];
            }
            remove_elem(parent, val_down);
            free(node);
        } else {
            printf("%s line %d\n", __func__, __LINE__);
            val_down = parent->vals[index];
            insert_elem(node, val_down);
            for (int i = 0; i < brother->len; i++) {
                node->childs[node->len] = brother->childs[i];
                insert_elem(node, brother->vals[i]);
            }
            node->childs[node->len] = brother->childs[brother->len];
            for (int i = index; i < parent->len + 1; i++) {
                parent->childs[i] = parent->childs[i+1];
            }
            remove_elem(parent, val_down);
            free(brother);
        }
        printf("%s line %d\n", __func__, __LINE__);
        node = parent;
    }
}

static struct Node* find(struct Node *root, int val) {
    while (root != NULL) {
        int i = 0;
        for (; i < root->len; i++) {
            if (root->vals[i] == val) {
                return root;
            }
            if (root->vals[i] > val) {
                break;
            }
        }
        root = root->childs[i];
    }
    return NULL;
}

static struct Node* find_max(struct Node *node) {
    while (node != NULL && node->childs[node->len] != NULL) {
        node = node->childs[node->len];
    }
    return node;
}

static struct Node* find_min(struct Node *node) {
    while (node != NULL && node->childs[0] != NULL) {
        node = node->childs[0];
    }
    return node;
}
