#include <stdio.h>
#include <stdlib.h>

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
    int max = 300; // 注意300表示最大值为299
    int *nums = (int *) malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % max;
    }
    array_print(nums, len);

    int *tmps = (int *) malloc(max * sizeof(int));
    for (int i = 0; i < max; i++) {
        tmps[i] = 0;
    }

    for (int i = 0; i < len; i++) {
        tmps[nums[i]] += 1;
    }

    int index = 0;
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < tmps[i]; j++) {
            nums[index++] = i;
        }
    }
    array_print(nums, len);
}
