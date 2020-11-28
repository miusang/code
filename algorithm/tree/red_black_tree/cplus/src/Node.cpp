#include "Node.h"
#include <stddef.h>

Node::Node() {
    val = 0;
    color = red;
    parent = NULL;
    left = NULL;
    right = NULL;
}

Node::Node(int val) {
    this->val = val;
    this->color = red;
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
}

Color Node::getColor(Node *node) {
    if (node == NULL) {
        return black;
    }
    return node->color;
}
