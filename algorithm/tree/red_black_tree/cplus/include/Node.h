#ifndef _NODE_H_
#define _NODE_H_

enum Color {
    black, red
};

class Node {
    public:
        Node();
        Node(int val);
        int val;
        Color color;
        Node *parent;
        Node *left;
        Node *right;
        static Color getColor(Node *node);
};

#endif
