#include <stdio.h>
#include <stdlib.h>

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    int len = atoi(argv[1]);
    int *nums = (int *) malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);

    for (int i = 0; i < len; i++) {
        int min_val = nums[i];
        int min_index = i;
        for (int j = i; j < len; j++) {
            if (nums[j] < min_val) {
                min_val = nums[j];
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(&nums[i], &nums[min_index]);
        }
    }
    array_print(nums, len);
    free(nums);
    return 0;
}
