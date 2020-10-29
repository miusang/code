#include <stdio.h>
#include <stdlib.h>

class MergeSort {
public:
    static void sort(int *nums, int *tmps, int start, int end);
    static void sort2(int *nums, int *tmps, int len);

private:
    static void merge(int *nums, int *tmps, int start, int mid, int end);
};

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
    int *tmps = new int[len];
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);
    MergeSort::sort(nums, tmps, 0, len - 1);
    //MergeSort::sort2(nums, tmps, len);
    array_print(nums, len);
}

void MergeSort::sort2(int *nums, int *tmps, int len) {
    for (int count = 2; count < len * 2; count = count * 2) {
        for (int start = 0; start < len; start += count) {
            int start1 = start;
            int end1 = start + count / 2 - 1;
            if (end1 >= len - 1) {
                break;
            }
            int start2 = end1 + 1;
            int end2 = start + count - 1;
            end2 = end2 >= len ? len - 1 : end2;
            int index = 0;
            int index1 = start1;
            int index2 = start2;
            while (index1 <= end1 && index2 <= end2) {
                tmps[index++] = nums[index1] <= nums[index2] ? nums[index1++] :
                    nums[index2++];
            }
            while (index1 <= end1) {
                tmps[index++] = nums[index1++];
            }
            while (index2 <= end2) {
                tmps[index++] = nums[index2++];
            }
            index = 0;
            while (index < end2 - start1 + 1) {
                nums[start + index] = tmps[index];
                index++;
            }
        }
    }
}

void MergeSort::sort(int *nums, int *tmps, int start, int end) {
    if (start >= end) {
        return;
    }
    int mid = (start + end) / 2;
    sort(nums, tmps, start, mid);
    sort(nums, tmps, mid + 1, end);
    merge(nums, tmps, start, mid, end);
}

void MergeSort::merge(int *nums, int *tmps, int start, int mid, int end) {
    int index = 0;
    int index1 = start;
    int index2 = mid + 1;
    while (index1 <= mid && index2 <= end) {
        tmps[index++] = nums[index1] <= nums[index2] ? nums[index1++] : 
            nums[index2++];
    }
    while (index1 <= mid) {
        tmps[index++] = nums[index1++];
    }
    while (index2 <= end) {
        tmps[index++] = nums[index2++];
    }
    index = 0;
    while (index < end - start + 1) {
        nums[index + start] = tmps[index];
        index++;
    }
}
