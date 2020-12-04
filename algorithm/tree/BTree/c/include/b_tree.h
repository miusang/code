#ifndef _B_TREE_H_
#define _B_TREE_H_
#include "node.h"

void insert(struct Node **root, int val);
int erase(struct Node **root, int val);
void inorder_visit(struct Node *root);
void level_visit(struct Node *root);

#endif
