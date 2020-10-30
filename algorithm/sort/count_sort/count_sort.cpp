#include <stdio.h>
#include <stdlib.h>

void sort(int *nums, int len);

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        return 0;
    }
    int len = atoi(argv[1]);
    int *nums = new int[len];
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
        if (nums[i] > max_val) {
            max_val = nums[i];
        }
    }
    int *tmps = new int[max_val + 1];
    for (int i = 0; i < max_val; i++) {
        tmps[i] = 0;
    }
    for (int i = 0; i < len; i++) {
        tmps[nums[i]] += 1;
    }
    int index = 0;
    for (int i = 0; i < max_val + 1; i++) {
        int j = 0;
        while (j < tmps[i]) {
            nums[index++] = i;
            j++;
        }
    }
    delete []tmps;
}
