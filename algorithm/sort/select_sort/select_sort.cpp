#include <stdio.h>
#include <stdlib.h>

class SelectSort {
public:
    static void sort(int *nums, int len);

private:
    static void swap(int &a, int &b);
};

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    int len = atoi(argv[1]);
    int *nums = new int[len];
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);
    SelectSort::sort(nums, len);
    array_print(nums, len);
}

void SelectSort::sort(int *nums, int len) {
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
            swap(nums[min_index], nums[i]);
        }
    }
}

void SelectSort::swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
