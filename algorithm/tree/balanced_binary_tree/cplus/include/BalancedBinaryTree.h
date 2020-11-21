#ifndef _BALANCED_BINARY_TREE_H_
#define _BALANCED_BINARY_TREE_H_

#include "Node.h"

class BalancedBinaryTree {
public:
    BalancedBinaryTree();
    ~BalancedBinaryTree();
    bool insert(int val);
    bool remove(int val);
    Node *root;

private:
    Node *find(int val);
    Node *findMax(Node *node);
    Node *findMin(Node *node);
    void leftRotate(Node *node);
    void rightRotate(Node *node);
    void balance(Node *node);
    int max(int a, int b);
};

#endif
