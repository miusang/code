#include "binary_tree.h"
#include "balanced_binary_tree.h"
#include <stdlib.h>
#include <stdio.h>

void array_print(int *nums, int len);
int main(int argc, const char* argv[]) {
    if (argc < 2) {
        return 0;
    }
    int len = atoi(argv[1]);
    int *nums = (int *) malloc(len * sizeof(int));
    struct Node* root = NULL; // 注意初始化！！！与malloc初始化不同.
    for (int i = 0; i < len;) {
        int val = rand() % 1000;
        if (insert(&root, val)) {
            nums[i] = val;
            i++;
        }
    }
    array_print(nums, len);
    printf("root height %d\n", get_height(root));
    inorder_visit(root);
    for (int i = 0; i < len; i++) {
        delete(&root, nums[i]);
        inorder_visit(root);
    }
    free(nums);
    return 0;
}

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
