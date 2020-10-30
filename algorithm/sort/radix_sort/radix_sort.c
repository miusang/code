#include <stdio.h>
#include <stdlib.h>

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void sort(int *nums, int len);

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        return 0;
    }
    int len = atoi(argv[1]);
    int *nums = (int *) malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);
    sort(nums, len);
    array_print(nums, len);
}

void sort(int *nums, int len) {
    int max_val = nums[0];
    for (int i = 0; i < len; i++) {
        max_val = nums[i] > max_val ? nums[i] : max_val;
    }
    int bit_count = 1;
    while (max_val / 10 > 0) { // 按10进制
        max_val = max_val / 10;
        bit_count += 1;
    }
    for (int i = 0; i < bit_count; i++) {
        int bit = 1;
        int j = 0;
        while (j < i) {
            bit = bit * 10;
            j++;
        }
        // 此处插入排序，可替换其他排序算法
        for (j = len - 1; j >= 0; j--) {
            int tmp = nums[j];
            int k = j + 1;
            while (k < len && (nums[k] / bit % 10) < (tmp / bit % 10)) {
                nums[k - 1] = nums[k];
                k++;
            }
            nums[k - 1] = tmp;
        }
    }
}
