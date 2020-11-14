#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__
#include <stddef.h>

struct Node {
    int val;
    Node *left;
    Node *right;
    Node(int val) {
        this->val = val;
        left = NULL;
        right = NULL;
    }
};

class BinaryTree {
public:
    static void inorderVisit(Node *root);
};

#endif
