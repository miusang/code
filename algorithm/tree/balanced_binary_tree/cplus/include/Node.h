#ifndef _NODE_H_
#define _NODE_H_

class Node {
public:
    Node();
    Node(int val);
    static int getHeight(Node *node);
    static int getFactor(Node *node);

public:
    int val;
    int height;
    Node *parent;
    Node *left;
    Node *right;
};

#endif
