#include <stdio.h>
#include <stdlib.h>
#include <vector>
using std::vector;

void array_print(int *nums, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}

void insert_sort(vector<int> &nums) {
    int i, j;
    for (i = nums.size() - 1; i > 0; i--) {
        j = i;
        int tmp = nums[i - 1];
        while (j < nums.size() && nums[j] < tmp) {
            nums[j - 1] = nums[j];
            j++;
        }
        nums[j - 1] = tmp;
    }
    for (i = 0; i < nums.size(); i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
    
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 0;
    }
    int len = atoi(argv[1]);
    int *nums = new int[len];
    for (int i = 0; i < len; i++) {
        nums[i] = rand() % 300;
    }
    array_print(nums, len);

    // 1. put elements of nums into bucket.
    int max_val = nums[0];
    int min_val = nums[0];
    for (int i = 1; i < len; i++) {
        if (max_val < nums[i]) {
            max_val = nums[i];
        }
        if (min_val > nums[i]) {
            min_val = nums[i];
        }
    }

    int bucket_step = len;
    int bucket_count = (max_val - min_val) / bucket_step + 1;
    vector<int> *buckets = new vector<int>[bucket_count];
    for (int i = 0; i < len; i++) {
        int bucket_index = (nums[i] - min_val) / bucket_step;
        buckets[bucket_index].push_back(nums[i]);
    }

    for (int i = 0; i < bucket_count; i++) { 
        insert_sort(buckets[i]);
    }

    int k = 0;
    for (int i = 0; i < bucket_count; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            nums[k] = buckets[i][j];
            k++;
        }
    }

    array_print(nums, len);

    return 0;
}
