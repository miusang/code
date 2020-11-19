#include "node.h"
#include <stddef.h>

int get_height(struct Node *node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

int get_factor(struct Node *node) {
    if (node == NULL) {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}
