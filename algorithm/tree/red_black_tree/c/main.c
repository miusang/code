#include "binary_tree.h"
#include "red_black_tree.h"
#include <stdio.h>
#include <stdlib.h>

void array_print(int *nums, int len);
int main(int argc, const char*argv[]) {
    if (argc < 2) {
        return 0;
    }
    int len = atoi(argv[1]);
    int *nums = (int *) malloc(len * sizeof(int));
    struct Node *root = NULL;
    for (int i = 0; i < len;) {
        int val = rand() % 1000;
        if (insert(&root, val)) {
            nums[i] = val;
            i++;
        }
    }
    array_print(nums, len);
    inorder_visit(root);
    level_visit(root);
    return 0;
}

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
