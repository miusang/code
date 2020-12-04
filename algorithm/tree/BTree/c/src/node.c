#include "node.h"
#include <stdlib.h>

struct Node* new_node() {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->len = 0;
    node->parent = NULL;
    for (int i = 0; i < TREE_M; i++) {
        node->childs[i] = NULL;
    }
    return node;
}

int insert_elem(struct Node *node, int val) {
    int i = node->len - 1;
    while (i >= 0 && node->vals[i] > val) {
        node->vals[i+1] = node->vals[i];
        i--;
    }
    node->vals[i+1] = val;
    node->len += 1;
    return i + 1;
}

int remove_elem(struct Node *node, int val) {
    for (int i = 0; i < node->len; i++) {
        if (node->vals[i] == val) {
            int j = i;
            while (j < node->len - 1) {
                node->vals[j] = node->vals[j+1];
                j++;
            }
            node->len--;
            return i;
        }
    }
    return -1;
}

int index_of_elem(struct Node *node, int val) {
    int start = 0;
    int end = node->len;
    while (start <= end) {
        int mid = (start + end) / 2;
        if (node->vals[mid] == val) {
            return mid;
        }
        if (node->vals[mid] < val) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return -1;
}

void insert_child(struct Node *node, struct Node *child, int index) {
    int i = node->len;
    while (i >= index) {
        node->childs[i + 1] = node->childs[i];
        i--;
    }
    node->childs[index] = child;
}
