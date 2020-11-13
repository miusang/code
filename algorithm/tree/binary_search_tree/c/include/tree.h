#ifndef _TREE_H_
#define _TREE_H_

struct Node {
    struct Node *left;
    struct Node *right;
    int val;
};

void preorder_visit(struct Node *root);
void inorder_visit(struct Node *root);
void postorder_visit(struct Node *root);

#endif
