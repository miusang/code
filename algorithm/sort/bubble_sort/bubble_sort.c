#include <stdio.h>

// C语言标准(C89)没有定义布尔类型。
typedef enum {true, false} bool;

/*
 * c不支持引用，只支持指针。
 */
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int nums[] = { 3, 5, 3, 0, 8, 11, 6, 12, 6, 1, 5, 8, 6, 2, 4, 9, 4, 7, 0,
        1, 8, 9, 7, 3, 1, 2, 57, 9, 200, 130, 7, 4, 0, 2, 6, 10};
    int len = sizeof(nums)/sizeof(int);
    printf("num lenth is: %d\n", len);
    for (int i = 0; i < len; i++) {
        bool flag = true;
        for (int j = 0; j < len - i - 1; j++) {
            if (nums[j] < nums[j+1]) {
                continue;
            }
            swap(&nums[j], &nums[j+1]);
            flag = false;
        }
        if (flag == true) {
            break;
        }
    }
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
