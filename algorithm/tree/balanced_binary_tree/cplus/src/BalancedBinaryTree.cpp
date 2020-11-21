#include "BalancedBinaryTree.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

BalancedBinaryTree::BalancedBinaryTree() {
    root = NULL;
}

BalancedBinaryTree::~BalancedBinaryTree() {
    while (root != NULL) {
        remove(root->val);
    }
}

bool BalancedBinaryTree::insert(int val) {
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
        return true;
    }
    if (parent->val > val) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    node->parent = parent;
    balance(node);
    return true;
}

bool BalancedBinaryTree::remove(int val) {
    Node *node = find(val);
    if (node == NULL) {
        return false;
    }
    Node *replace = findMax(node->left);
    if (replace == NULL) {
        replace = findMin(node->right);
    }
    if (replace == NULL) { // 叶子节点
        if (node->parent == NULL) { // 根节点
            root = NULL;
            delete node;
            return true;
        }
        if (node == node->parent->left) {
            node->parent->left = NULL;
        } else {
            node->parent->right = NULL;
        }
        balance(node);
        delete node;
        return true;
    }
    if (replace->val > val) { // 后继
        if (replace == replace->parent->left) {
            replace->parent->left = replace->right;
        } else {
            replace->parent->right = replace->right;
        }
        if (replace->right != NULL) {
            replace->right->parent = replace->parent;
        }
    } else {
        if (replace == replace->parent->left) {
            replace->parent->left = replace->left;
        } else {
            replace->parent->right = replace->left;
        }
        if (replace->left != NULL) {
            replace->left->parent = replace->parent;
        }
    }
    node->val = replace->val;
    balance(replace);
    delete replace;
    return true;
}

void BalancedBinaryTree::balance(Node *node) {
    while (node != NULL && node->parent != NULL) {
        node = node->parent;
        int fac = Node::getFactor(node);
        if (abs(fac) <= 1) {
            int childHeight = max(Node::getHeight(node->left),
                    Node::getHeight(node->right));
            if (childHeight + 1 == node->height) {
                return;
            }
            node->height = childHeight + 1;
            continue;
        }
        if (fac > 0) {
            int facLeft = Node::getFactor(node->left);
            if (facLeft < 0) {
                leftRotate(node->left);
            }
            rightRotate(node);
        } else {
            int facRight = Node::getFactor(node->right);
            if (facRight > 0) {
                rightRotate(node->right);
            }
            leftRotate(node);
        }
    }
}

Node* BalancedBinaryTree::find(int val) {
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

Node* BalancedBinaryTree::findMax(Node *node) {
    while (node != NULL && node->right != NULL) {
        node = node->right;
    }
    return node;
}

Node* BalancedBinaryTree::findMin(Node *node) {
    while (node != NULL && node->left != NULL) {
        node = node->left;
    }
    return node;
}

void BalancedBinaryTree::leftRotate(Node *node) {
    if (node == NULL || node->right == NULL) {
        return;
    }
    Node *parent = node->parent;
    Node *right = node->right;
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
    node->height = max(Node::getHeight(node->left), 
            Node::getHeight(node->right)) + 1;

    right->left = node;
    node->parent = right;
    right->height = max(Node::getHeight(right->left),
            Node::getHeight(right->right)) + 1;
}

void BalancedBinaryTree::rightRotate(Node *node) {
    if (node == NULL || node->left == NULL) {
        return;
    }
    Node *parent = node->parent;
    Node *left = node->left;

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
    node->height = max(Node::getHeight(node->left),
            Node::getHeight(node->right)) + 1;

    left->right = node;
    node->parent = left;
    left->height = max(Node::getHeight(left->left),
            Node::getHeight(left->right)) + 1;
}

int BalancedBinaryTree::max(int a, int b) {
    return a > b ? a : b;
}
