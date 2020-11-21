#include <stdio.h>
#include <stdlib.h>
#include "BalancedBinaryTree.h"
#include "BinaryTree.h"

void array_print(int *nums, int len);
int main(int argc, const char* argv[]) {
    if (argc < 2) {
        return 0;
    }
    int len = atoi(argv[1]);
    int *nums = new int[len];
    BalancedBinaryTree *tree = new BalancedBinaryTree();
    for (int i = 0; i < len;) {
        int val = rand() % 1000;
        if (tree->insert(val)) {
            nums[i] = val;
            i++;
        }
    }
    array_print(nums, len);
    printf("tree height %d\n", Node::getHeight(tree->root));
    BinaryTree::inorderVisit(tree->root);
    
    for (int i = 0; i < len; i++) {
        tree->remove(nums[i]);
        BinaryTree::inorderVisit(tree->root);
    }
    delete[] nums;
    delete tree;

    return 0;
}

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
