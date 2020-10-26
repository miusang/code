#include <stdio.h>
#include <stdlib.h>

void array_print(int *nums, int len);
void sort(int *nums, int start, int end);
int get_pivot(int *nums, int start, int end);
void swap(int *a, int *b);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("please intput nums length.\n");
    }
    int len = atoi(argv[1]);
    int *nums = (int *) malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);
    sort(nums, 0, len - 1);
    array_print(nums, len);
}

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

int get_pivot(int *nums, int start, int end) {
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

void sort(int *nums, int start, int end) {
    if (start >= end) {
        return;
    }
    int pivot = get_pivot(nums, start, end);
    int i = start;
    int j = end;
    while (i < j) {
        if (i < pivot && nums[i] <= nums[pivot]) {
            i++;
            continue;
        }
        if (nums[i] > nums[pivot]) {
            swap(&nums[i], &nums[pivot]);
            pivot = i;
        }
        if (j > pivot && nums[j] >= nums[pivot]) {
            j--;
            continue;
        }
        swap(&nums[j], &nums[pivot]);
        pivot = j;
    }
    sort(nums, start, pivot - 1);
    sort(nums, pivot + 1, end);
}
