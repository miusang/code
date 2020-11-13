#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tree.h"


int insert(struct Node **root, int val);
int delete(struct Node **root, int val);

/**
 * 寻找最大和最小是为了找到一个节点的前驱和后继。
 *
 * 其中关于一个节点的前驱和后继的定义如下：
 * 前驱：二叉搜索树中序遍历，按遍历后的顺序，当前节点的前一个节点。
 * 后继：二叉搜索树中序遍历，按遍历后的顺序，当前节点的后一个节点。
 */
struct Node* find(struct Node **root, int val, struct Node **parent);
struct Node* findMax(struct Node **root, struct Node **parent);
struct Node* findMin(struct Node **root, struct Node **parent);

void array_print(int *nums, int len);
int main(int argc, const char*argv[]) {
    int MAX = 300;
    if (argc < 2) {
        return 0;
    }
    
    int len = atoi(argv[1]);
    if (len >= MAX) {
        return 0;
    }
    int *nums = (int *) malloc(len * sizeof(int));
    struct Node *root = NULL;
    struct Node *node = NULL;
    int i = 0;
    while (i < len) {
        int val = rand() % MAX;
        if (insert(&root, val) == 0) {
            nums[i] = val;
            i++;
        }
    }
    array_print(nums, len);
    inorder_visit(root);
    
    printf("\n--------------------for delete------------\n");
    for (int i = 0; i < len;) {
        inorder_visit(root);
        if(delete(&root, nums[i]) == 0) {
            i++;
        }
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

int insert(struct Node **root, int val) {
    struct Node *pre = NULL;
    struct Node *cur = *root;
    while (cur != NULL) {
        if (cur->val == val) {
            return -1;
        }
        if (cur->val < val) {
            pre = cur;
            cur = cur->right;
        } else {
            pre = cur;
            cur = cur->left;
        }
    }
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    node->val = val;
    if (pre == NULL) {
        *root = node;
        return 0;
    }
    if (pre->val < val) {
        pre->right = node;
    } else {
        pre->left = node;
    }
    return 0;
}

struct Node* find(struct Node **root, int val, struct Node **parent) {
    *parent = NULL;
    struct Node *cur = *root;
    while (cur != NULL) {
        if (cur->val == val) {
            return cur;
        }
        *parent = cur;
        if (cur->val < val) {
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
    *parent = NULL;
    return NULL;
}

struct Node* findMin(struct Node **root, struct Node **parent) {
    *parent = NULL;
    if (root == NULL || *root == NULL) {
        return NULL;
    }
    struct Node *cur = *root;
    while (cur->left != NULL) {
        *parent = cur;
        cur = cur->left;
    }
    return cur;
}

struct Node* findMax(struct Node **root, struct Node **parent) {
    *parent = NULL;
    if (root == NULL || *root == NULL) {
        return NULL;
    }
    struct Node *cur = *root;
    while (cur->right != NULL) {
        *parent = cur;
        cur = cur->right;
    }
    return cur;
}

int delete(struct Node **root, int val) {
    struct Node *parent;
    struct Node *node = find(root, val, &parent);
    if (node == NULL) {
        return -1;
    }
    //printf("delete val: %d\n", node->val);
    
    struct Node *replace_parent;
    struct Node *replace = findMin(&node->right, &replace_parent);
    if (replace == NULL) {
        replace = findMax(&node->left, &replace_parent);
    }

    if (replace_parent == NULL) {
        replace_parent = node;
    }
    if (replace_parent == NULL) {
        *root = NULL;
        free(node);
        return 0;
    }
    if(replace == NULL) {
        //printf("leave point\n");
        if (parent != NULL && parent->left == node) {
            parent->left = NULL;
        }
        if (parent != NULL && parent->right == node) {
            parent->right = NULL;
        }
        free(node);
        return 0;
    }
    //printf("replace val: %d\n", replace->val);
    if (node->val > replace->val) { // 前驱节点，没有右子树
        if (replace == replace_parent->left) {
            replace_parent->left = replace->left;
        } else {
            replace_parent->right = replace->left;
        }
    } else { // 后继节点，没有左子树
        if (replace == replace_parent->left) {
            replace_parent->left = replace->right;
        } else {
            replace_parent->right = replace->right;
        }
    }
    node->val = replace->val;
    free(replace);
    return 0;
}
