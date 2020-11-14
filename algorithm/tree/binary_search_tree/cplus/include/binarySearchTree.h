#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_
#include "binaryTree.h"

class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();
    int insert(int val);
    int remove(int val);
    Node *getRoot();
    Node *find(int val);

private:
    Node *root;
    Node *find(int val, Node **parent);
    Node *findMax(Node *node, Node **parent);
    Node *findMin(Node *node, Node **parent);
};

#endif
