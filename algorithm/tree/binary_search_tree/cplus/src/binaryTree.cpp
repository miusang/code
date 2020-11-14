#include "binaryTree.h"
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
        root = list.at(list.size() - 1);
        list.pop_back();
        printf("%d ", root->val);
        root = root->right;
    }
    printf("\n");
}
