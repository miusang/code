#include "RedBlackTree.h"
#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

void array_print(int *nums, int len);
int main(int argc, const char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    int len = atoi(argv[1]);
    int *nums = new int[len];
    RedBlackTree *tree = new RedBlackTree();
    for (int i = 0; i < len;) {
        int val = rand() % 1000;
        if (tree->insert(val)) {
            nums[i++] = val;
        }
    }
    array_print(nums, len);
    BinaryTree::inorderVisit(tree->root);
    BinaryTree::levelVisit(tree->root);
    for (int i = 0; i < len; i++) {
        tree->remove(nums[i]);
        BinaryTree::inorderVisit(tree->root);
    }
    delete []nums;
    return 0;
}

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
