#include "tree.h"
#include <stdio.h>

void preorder_visit(struct Node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preorder_visit(root->left);
    preorder_visit(root->right);
}

// 二叉搜索树中序遍历是一个有序序列
void inorder_visit(struct Node *root) {
    if (root == NULL) {
        return;
    }
    inorder_visit(root->left);
    printf("%d ", root->val);
    inorder_visit(root->right);
}
