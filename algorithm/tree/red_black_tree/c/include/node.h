#ifndef _NODE_H_
#define _NODE_H_

enum Color {
    red, black
};

struct Node {
    int val;
    enum Color color;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
};

enum Color get_color(struct Node* node);

#endif
