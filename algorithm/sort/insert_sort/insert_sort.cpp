#include <stdio.h>
#include <stdlib.h>

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
int main() {
    int nums[50];
    int len = sizeof(nums) / sizeof(int);
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);

    int i, j;
    for (i = len - 1; i > 0; i--) {
        int tmp = nums[i - 1];
        j = i;
        while (j < len && nums[j] < tmp) {
            nums[j-1] = nums[j];
            j++;
        }
        nums[j-1] = tmp;
    }

    array_print(nums, len);
}
