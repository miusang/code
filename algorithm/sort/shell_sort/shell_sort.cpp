#include <stdio.h>
#include <stdlib.h>

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    int len = atoi(argv[1]);
    printf("nums len %d\n", len);

    int *nums = new int[len];
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);

    int i,j;
    for (int gap = len / 2; gap > 0; gap = gap / 2) {
        for (int i = len - gap; i >= gap; i--) {
            int tmp = nums[i - gap];
            int j = i;
            while (j < len && nums[j] < tmp) {
                nums[j - gap] = nums[j];
                j += gap;
            }
            nums[j - gap] = tmp;
        }
    }

    array_print(nums, len);
}
