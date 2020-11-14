#include "binarySearchTree.h"
#include <stddef.h>
#include <stdio.h>

BinarySearchTree::BinarySearchTree() {
    root = NULL;
}

BinarySearchTree::~BinarySearchTree() {
    while(root != NULL) {
        remove(root->val);
    }
}

int BinarySearchTree::insert(int val) {
    Node *cur = root;
    Node *parent = NULL;
    while (cur != NULL) {
        if (cur->val == val) {
            return -1;
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
        return 0;
    }
    if (parent->val > val) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    return 0;
}

int BinarySearchTree::remove(int val) {
    Node *parent = NULL;
    Node *node = find(val, &parent);
    if (node == NULL) {
        return -1;
    }
    Node *replace_parent = node;
    Node *replace = findMax(node->left, &replace_parent);
    if (replace == NULL) {
        replace_parent = node;
        replace = findMin(node->right, &replace_parent);
    }
    if (replace == NULL) {
        if (parent == NULL) {
            root = NULL;
            delete node;
            return 0;
        }
        if (parent->left == node) {
            parent->left = NULL;
        } else {
            parent->right = NULL;
        }
        delete node;
        return 0;
    }
    if (replace->val > node->val) { // 后继
        if (replace == replace_parent->left) {
            replace_parent->left = replace->right;
        } else {
            replace_parent->right = replace->right;
        }
    } else { // 前驱
        if (replace == replace_parent->left) {
            replace_parent->left = replace->left;
        } else {
            replace_parent->right = replace->left;
        }
    }
    node->val = replace->val;
    delete replace;
    return 0;
}

Node* BinarySearchTree::getRoot() {
    return root;
}

Node* BinarySearchTree::find(int val, Node **parent) {
    Node *cur = root;
    *parent = NULL;
    while (cur != NULL) {
        if (cur->val == val) {
            return cur;
        }
        *parent = cur;
        if (cur->val > val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return NULL;
}

Node* BinarySearchTree::findMax(Node *node, Node **parent) {
    if (node == NULL) {
        return NULL;
    }
    while (node->right != NULL) {
        *parent = node;
        node = node->right;
    }
    return node;
}

Node* BinarySearchTree::findMin(Node *node, Node **parent) {
    if (node == NULL) {
        return NULL;
    }
    while (node->left != NULL) {
        *parent =  node;
        node = node->left;
    }
    return node;
}
