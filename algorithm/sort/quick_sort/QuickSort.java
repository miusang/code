import java.util.Arrays;
import java.util.Random;

public class QuickSort {
    public static void main(String[] args) {
        if (args.length < 1) {
            return;
        }
        int len = Integer.parseInt(args[0]);
        int[] nums = new int[len];
        Random random = new Random();
        for (int i = 0; i < nums.length; i++) {
            nums[i] = random.nextInt(300);
        }
        System.out.println(Arrays.toString(nums));
        sort(nums, 0, nums.length - 1);
        System.out.println(Arrays.toString(nums));
    }

    public static void sort(int[] nums, int start, int end) {
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
                swap(nums, i, pivot);
                pivot = i;
            }
            if (j > pivot && nums[j] >= nums[pivot]) {
                j--;
                continue;
            }
            swap(nums, j, pivot);
            pivot = j;
        }
        sort(nums, start, pivot - 1);
        sort(nums, pivot + 1, end);
    }

    private static int getPivot(int[] nums, int start, int end) {
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

    private static void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
