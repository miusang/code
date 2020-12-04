#include "b_tree.h"
#include <stdio.h>
#include <stdlib.h>

void array_print(int *nums, int len);
void main(int argc, const char* argv[]) {
    if (argc < 2) {
        return;
    }
    int len = atoi(argv[1]);
    int *nums = (int *) malloc(len * sizeof(int));
    struct Node *root = NULL;
    for (int i = 0; i < len; i++) {
        int val = rand() % 1000;
        insert(&root, val);
        nums[i] = val;
    }
    array_print(nums, len);
    printf ("root vals: ");
    for (int i = 0; i < root->len; i++) {
        printf("%d ", root->vals[i]);
    }
    printf("\n");
    inorder_visit(root);
    printf("\n");
    /*
    for (int i = 0; i < len; i++) {
        erase(&root, nums[i]);
        inorder_visit(root);
        printf("\n");
    }*/
    free(nums);
}

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
