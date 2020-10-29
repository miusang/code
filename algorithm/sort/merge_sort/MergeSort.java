import java.util.Arrays;
import java.util.Random;

public class MergeSort {
    public static void main(String[] args) {
        if (args.length < 1) {
            return;
        }
        int len = Integer.parseInt(args[0]);
        int[] nums = new int[len];
        int[] tmps = new int[len];
        Random random = new Random();
        for (int i = 0; i < len; i++) {
            nums[i] = random.nextInt(300);
        }
        System.out.println(Arrays.toString(nums));
        //sort(nums, tmps, 0, nums.length - 1);
        sort2(nums, tmps);
        System.out.println(Arrays.toString(nums));
    }

    public static void sort(int[] nums, int[] tmps, int start, int end) {
        if (start >= end) {
            return;
        }
        int mid = (start + end) / 2;
        sort(nums, tmps, start, mid);
        sort(nums, tmps, mid + 1, end);
        merge(nums, tmps, start, mid, end);
    }

    private static void merge(int[] nums, int[] tmps, int start, int mid, 
            int end) {
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

    public static void sort2(int[] nums, int[] tmps){
        for (int count = 2; count < nums.length * 2; count = count * 2) {
            for (int start = 0; start < nums.length; start += count) {
                int index1 = start;
                int end1 = start + count / 2 - 1;
                if (end1 >= nums.length - 1) {
                    break;
                }
                int index2 = end1 + 1;
                int end2 = start + count - 1;
                end2 = end2 >= nums.length ? nums.length - 1 : end2;
                int index = 0;
                while (index1 <= end1 && index2 <= end2) {
                    tmps[index++] = nums[index1] <= nums[index2] ? 
                        nums[index1++] : nums[index2++];
                }
                while (index1 <= end1) {
                    tmps[index++] = nums[index1++];
                }
                while (index2 <= end2) {
                    tmps[index++] = nums[index2++];
                }
                index = 0;
                while (index < end2 - start + 1) {
                    nums[start + index] = tmps[index];
                    index++;
                }
            }
        }
    }
}
