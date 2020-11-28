#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_
#include "Node.h"
#include <stdbool.h>

class RedBlackTree{
    public:
        RedBlackTree();
        ~RedBlackTree();
        Node *root;
        bool insert(int val);
        bool remove(int val);

    private:
        void insertFix(Node *node);
        void removeFix(Node *node, bool isLeft);
        void leftRotate(Node *node);
        void rightRotate(Node *node);
        Node* find(int val);
        Node* findMax(Node *node);
        Node* findMin(Node *node);
};

#endif
