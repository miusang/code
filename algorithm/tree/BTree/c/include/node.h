#ifndef _NODE_H_
#define _NODE_H_

#define TREE_M 3

struct Node {
    int vals[TREE_M]; // 多一个备用
    int len;
    struct Node *parent;
    struct Node *childs[TREE_M + 1];
};

struct Node* new_node();
int insert_elem(struct Node *node, int val);
int remove_elem(struct Node *node, int val);
int index_of_elem(struct Node *node, int val);
void insert_child(struct Node *node, struct Node *child, int index);

#endif
