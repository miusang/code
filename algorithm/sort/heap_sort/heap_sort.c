#include <stdio.h>
#include <stdlib.h>

void sort(int *nums, int len);
void swap(int *a, int *b);

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main(int argc, const char*argv[]) {
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
    free(nums);
    return 0;
}

void sort(int *nums, int len) {
    for (int end = len - 1; end > 0; end--) {
        for (int p = (end - 1) / 2; p >= 0; p--) {
            int max = p;
            int left = p * 2 + 1;
            int right = p * 2 + 2;
            if (nums[left] > nums[max]) {
                max = left;
            }
            if (right <= end && nums[right] > nums[max]) {
                max = right;
            }
            if (max != p) {
                swap(&nums[p], &nums[max]);
            }
        }
        swap(&nums[0], &nums[end]);
    }
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
