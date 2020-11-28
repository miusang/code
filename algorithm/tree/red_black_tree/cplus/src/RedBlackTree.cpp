#include "RedBlackTree.h"
#include <stddef.h>
#include <stdio.h>

RedBlackTree::RedBlackTree() {
    root = NULL;
}

RedBlackTree::~RedBlackTree() {
    while (root != NULL) {
        remove(root->val);
    }
}

bool RedBlackTree::insert(int val) {
    Node *cur = root;
    Node *parent = NULL;
    while (cur != NULL) {
        if (cur->val == val) {
            return false;
        }
        parent = cur;
        if (cur->val > val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    Node *node = new Node(val);
    if (parent == NULL) {
        root = node;
    } else if (parent->val > val) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    node->parent = parent;
    insertFix(node);
    return true;
}

bool RedBlackTree::remove(int val) {
    Node *node = find(val);
    if (node == NULL) {
        return false;
    }
    Node *replace = findMax(node->left);
    if (replace == NULL) {
        replace = findMin(node->right);
    }
    bool isLeft;
    if (replace == NULL) {
        if (node->parent == NULL) {
            root = NULL;
            delete node;
            return true;
        }
        if (node == node->parent->left) {
            node->parent->left = NULL;
            isLeft = true;
        } else {
            node->parent->right = NULL;
            isLeft = false;
        }
        removeFix(node, isLeft);
        delete node;
        return true;
    }
    if (replace->val > val) { // 后继
        if (replace == replace->parent->left) {
            replace->parent->left = replace->right;
            isLeft = true;
        } else {
            replace->parent->right = replace->right;
            isLeft = false;
        }
        if (replace->right != NULL) {
            replace->right->parent = replace->parent;
        }
    } else {
        if (replace == replace->parent->left) {
            replace->parent->left = replace->left;
            isLeft = true;
        } else {
            replace->parent->right = replace->left;
            isLeft = false;
        }
        if (replace->left != NULL) {
            replace->left->parent = replace->parent;
        }
    }
    node->val = replace->val;
    removeFix(replace, isLeft);
    delete replace;
    return true;
}

void RedBlackTree::insertFix(Node *node) {
    while (node != NULL) {
        Node *p = node->parent;
        if (Node::getColor(p) == black) {
            if (p == NULL) {
                node->color = black;
            }
            return;
        }
        Node *g = p->parent;
        Node *u = NULL;
        if (p == g->left) {
            u = g->right;
        } else {
            u = g->left;
        }
        if (Node::getColor(u) == red) {
            p->color = black;
            u->color = black;
            g->color = red;
            node = g;
            continue;
        }
        g->color = red;
        if (p == g->left) {
            if (node == p->right) {
                leftRotate(p);
                p = p->parent;
            }
            p->color = black;
            rightRotate(g);
            return;
        }
        if (node == p->left) {
            rightRotate(p);
            p = p->parent;
        }
        p->color = black;
        leftRotate(g);
        return;
    }
}

void RedBlackTree::removeFix(Node *node, bool isLeft) {
    while (node != NULL && node->parent != NULL && node->color == black) {
        Node *p = node->parent;
        Node *w = NULL;
        if (isLeft) {
            w = p->right;
            if (Node::getColor(w) == red) {
                w->color = black;
                p->color = red;
                leftRotate(p);
                w = p->right;
            }
            if (Node::getColor(w->left) == black && 
                    Node::getColor(w->right) == black) {
                w->color = red;
                node = p;
            } else {
                if (Node::getColor(w->right) == black) {
                    w->left->color = black;
                    w->color = red;
                    rightRotate(w);
                    w = p->right;
                }
                w->color = p->color;
                p->color = black;
                w->right->color = black;
                leftRotate(p);
                node = root;
                continue;
            }
            if (node->parent != NULL) {
                isLeft = node == node->parent->left;
            }
            continue;
        }
        w = p->left;
        if (Node::getColor(w) == red) {
            w->color = black;
            p->color = red;
            rightRotate(p);
            w = p->left;
        }
        if (Node::getColor(w->left) == black &&
                Node::getColor(w->right) == black) {
            w->color = red;
            node = p;
        } else {
            if (Node::getColor(w->left) == black) {
                w->right->color = black;
                w->color = red;
                leftRotate(w);
                w = p->left;
            }
            w->color = p->color;
            p->color = black;
            w->left->color = black;
            rightRotate(p);
            node = root;
            continue;
        }
        if (node->parent != NULL) {
            isLeft = node == node->parent->left;
        }
    }
    node->color = black;
}

void RedBlackTree::leftRotate(Node *node) {
    if (node == NULL || node->right == NULL) {
        return;
    }
    Node *right = node->right;
    Node *parent = node->parent;
    if (parent == NULL) {
        root = right;
    } else if (node == parent->left) {
        parent->left = right;
    } else {
        parent->right = right;
    }
    right->parent = parent;

    node->right = right->left;
    if (node->right != NULL) {
        node->right->parent = node;
    }

    right->left = node;
    node->parent = right;
}

void RedBlackTree::rightRotate(Node *node) {
    if (node == NULL || node->left == NULL) {
        return;
    }
    Node *left = node->left;
    Node *parent = node->parent;
    if (parent == NULL) {
        root = left;
    } else if (node == parent->left) {
        parent->left = left;
    } else {
        parent->right = left;
    }
    left->parent = parent;

    node->left = left->right;
    if (node->left != NULL) {
        node->left->parent = node;
    }

    left->right = node;
    node->parent = left;
}

Node* RedBlackTree::find(int val) {
    Node *cur = root;
    while (cur != NULL) {
        if (cur->val == val) {
            return cur;
        }
        if (cur->val > val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return NULL;
}

Node* RedBlackTree::findMax(Node *node) {
    while (node != NULL && node->right != NULL) {
        node = node->right;
    }
    return node;
}

Node* RedBlackTree::findMin(Node *node) {
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }
    return node;
}
