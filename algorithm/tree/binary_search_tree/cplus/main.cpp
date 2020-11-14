#include "binarySearchTree.h"
#include <stdlib.h>
#include <stdio.h>

void array_print(int *nums, int len);
int main(int argc, const char*argv[]) {
    if (argc < 2) {
        return 0;
    }
    int MAX = 300;
    int len = atoi(argv[1]);
    if (len >= MAX) {
        return 0;
    }

    int *nums = new int[len];
    BinarySearchTree *bsTree = new BinarySearchTree();
    
    for (int i = 0; i < len;) {
        int val = rand() % MAX;
        if (bsTree->insert(val) == 0) {
            nums[i] = val;
            i++;
        }
    }

    array_print(nums, len);
    BinaryTree::inorderVisit(bsTree->getRoot());
    
    for (int i = 0; i < len; i++) {
        int flag = bsTree->remove(nums[i]);
        BinaryTree::inorderVisit(bsTree->getRoot());
    }

    delete bsTree;
    delete[] nums;
    return 0;
}

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
