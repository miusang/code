/*
 * @author:atom
 * @date:2020/10/15
 * @description: bubble sort implement with java.
 */

import java.util.Arrays;
public class BubbleSort {
    public static void main(String[] args) {
        int[] nums = new int[] {3, 5, 3, 0, 8, 11, 6, 12,  6, 1, 5, 8, 6, 2, 4,
            9, 4, 7, 0, 1, 8, 9, 7, 3, 1, 2, 57, 9, 200, 130, 7, 4, 0, 2, 6, 10};
        bubbleSort(nums);
        System.out.print("bubbleSort: ");
        System.out.println(Arrays.toString(nums));
    }
    public static void bubbleSort(int[] nums) {
        for (int i = 0; i < nums.length; i++) {
            boolean flag = true; // 有序标志位。
            for (int j = 0; j < nums.length - i - 1; j++) {
                if (nums[j] > nums[j + 1]) {
                    int tmp = nums[j];
                    nums[j] = nums[j + 1];
                    nums[j + 1] = tmp;
                    flag = false;
                }
            }
            if (flag) {
                // 如果未排序序列有序，则结束排序。
                return;
            }
        }
    }
}
