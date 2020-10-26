#include <stdio.h>
#include <stdlib.h>

class QuickSort {
public:
    static void sort(int *nums, int start, int end);

private:
    static int getPivot(int *nums, int start, int end);
    static void swap(int &a, int &b);
};

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("please input nums length.\n");
        return 0;
    }
    int len = atoi(argv[1]);
    int *nums = new int[len];
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);
    QuickSort::sort(nums, 0, len - 1);
    array_print(nums, len);
    QuickSort::sort(nums, 0, len - 1);
    return 0;
}

void QuickSort::sort(int *nums, int start, int end) {
    if (start >= end) {
        return;
    }
    int pivot = getPivot(nums, start, end);
    int i = start;
    int j = end;
    while (i < j) {
        if (i < pivot && nums[i] <= nums[pivot]) {
            i++;
            continue;
        }
        if (nums[i] > nums[pivot]) {
            swap(nums[i], nums[pivot]);
            pivot = i;
        }
        if (j > pivot && nums[j] >= nums[pivot]) {
            j--;
            continue;
        }
        swap(nums[j], nums[i]);
        pivot = j;
    }
    sort(nums, start, pivot - 1);
    sort(nums, pivot + 1, end);
}

int QuickSort::getPivot(int *nums, int start, int end) {
    int mid = (start + end) / 2;
    if (nums[start] >= nums[mid] && nums[start] <= nums[end]) {
        return start;
    }
    if (nums[start] >= nums[end] && nums[start] <= nums[mid]) {
        return start;
    }
    if (nums[mid] >= nums[start] && nums[mid] <= nums[end]) {
        return mid;
    }
    if (nums[mid] >= nums[end] && nums[mid] <= nums[start]) {
        return mid;
    }
    return end;
}

void QuickSort::swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
