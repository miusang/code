#ifndef _BINARY_TREE_H_
#define _BINATR_TREE_H_

#include "Node.h"
class BinaryTree {
    public:
        static void inorderVisit(Node *root);
        static void levelVisit(Node *root);
};
#endif
