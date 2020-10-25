#include <stdio.h>
#include <stdlib.h>

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void swap(int *a, int*b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int nums[50];
    int len = sizeof(nums) / sizeof(int);
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);
    
    int i,j;
    /*
    for (i = 1; i < len; i++) {
        int sorted_count = i;
        for (j = sorted_count - 1; j >=0 && nums[j+1] < nums[j]; j--) {
            swap(&nums[j], &nums[j+1]);
        }
    }*/

    /*
    for (int i = len - 1; i > 0; i--) {
        int non_sorted_num = nums[i - 1];
        for (j = i; j < len && non_sorted_num > nums[j]; j++) {
            nums[j - 1] = nums[j];
        }
        nums[j - 1] = non_sorted_num;
    }*/

    for (int i = len - 1; i > 0; i--) {
        int non_sorted_num = nums[i - 1];
        j = i;
        while (j < len && non_sorted_num > nums[j]) {
            nums[j - 1] = nums[j];
            j++;
        }
        nums[j - 1] = non_sorted_num;
    }

    array_print(nums, len);
}
