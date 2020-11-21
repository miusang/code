#include "Node.h"
#include <stddef.h>
#include <stdio.h>

Node::Node() {
    val = 0;
    height = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
}

Node::Node(int val) {
    this->val = val;
    this->height = 0;
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
}

int Node::getHeight(Node *node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

int Node::getFactor(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return Node::getHeight(node->left) - Node::getHeight(node->right);
}
