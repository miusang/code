#ifndef _NODE_H_
#define _NODE_H_
struct Node {
    int val;
    int height;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

int get_height(struct Node *node);
int get_factor(struct Node *node);

#endif
