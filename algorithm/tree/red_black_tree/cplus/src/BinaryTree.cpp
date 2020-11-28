#include "BinaryTree.h"
#include <stdio.h>
#include <vector>
using std::vector;

void BinaryTree::inorderVisit(Node *root) {
    vector<Node *> list;
    while (root != NULL || !list.empty()) {
        while (root != NULL) {
            list.push_back(root);
            root = root->left;
        }
        //root = list.back();
        root = list.at(list.size() - 1);
        list.pop_back();
        printf("%d ", root->val);
        root = root->right;
    }
    printf("\n");
}

void BinaryTree::levelVisit(Node *root) {
    if (root == NULL) {
        return;
    }
    vector<Node *> list;
    list.push_back(root);
    while (!list.empty()) {
        root = list.front();
        printf("%d(%d) ", root->val, root->color == black);
        list.erase(list.begin());
        if (root->left != NULL) {
            list.push_back(root->left);
        }
        if (root->right != NULL) {
            list.push_back(root->right);
        }
    }
    printf("\n");
}
