#include <stdio.h>
#include <stdlib.h>

void sort(int *nums, int *nums_sorted, int start, int end);
void merge(int *nums, int *nums_sorted, int start, int mid, int end);

void sort2(int *nums, int *nums_sorted, int len);

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
    int *nums = (int *) malloc(len * sizeof(int));
    int *nums_sorted = (int *) malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);
    //sort(nums, nums_sorted, 0, len - 1);
    sort2(nums, nums_sorted, len);
    array_print(nums, len);
    free(nums);
    free(nums_sorted);
    return 0;
}

void sort(int *nums, int *nums_sorted, int start, int end) {
    if (start >= end) {
        return;
    }
    int mid = (start + end) / 2;
    sort(nums, nums_sorted, start, mid);
    sort(nums, nums_sorted, mid + 1, end);
    merge(nums, nums_sorted, start, mid, end);
}

void merge(int *nums, int *nums_sorted, int start, int mid, int end) {
    int index1 = start;
    int index2 = mid + 1;
    int index = 0;
    while (index1 <= mid && index2 <= end) {
        nums_sorted[index++] = (nums[index1] <= nums[index2]) ? nums[index1++] : nums[index2++];
        /*
        if (nums[index1] <= nums[index2]) {
            nums_sorted[index++] = nums[index1++];
        } else {
            nums_sorted[index++] = nums[index2++];
        }*/
    }
    while (index1 <= mid) {
        nums_sorted[index++] = nums[index1++];
    }
    while (index2 <= end) {
        nums_sorted[index++] = nums[index2++];
    }
    index = 0;
    
    while (index < (end - start + 1)) {
        // 注意索引自增
        nums[start + index] = nums_sorted[index];
        index++;
    }
}

void sort2(int *nums, int *nums_sorted, int len) {
    for (int count = 2; count < len * 2; count = count * 2) {
        for (int i = 0; i < len; i += count) {
            int start1 = i;
            int start2 = start1 + count / 2;
            int end1 = start2 - 1;
            int end2 = start1 + count - 1;
            if (end1 > len - 1) {
                break;
            }
            end2 = end2 > len - 1 ? len - 1 : end2;
            int index = 0;
            int index1 = start1;
            int index2 = start2;
            while (index1 <= end1 && index2 <= end2) {
                nums_sorted[index++] = nums[index1] <= nums[index2] ? nums[index1++] : nums[index2++];
            }
            while (index1 <= end1) {
                nums_sorted[index++] = nums[index1++];
            }
            while (index2 <= end2) {
                nums_sorted[index++] = nums[index2++];
            }

            index = 0;
            while (index < end2 - start1 + 1) {
                // 注意索引自增
                nums[start1 + index++] = nums_sorted[index];
            }
        }
    }
}
