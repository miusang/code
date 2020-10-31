import java.util.Arrays;
import java.util.Random;

public class HeapSort {
    public static void main(String[] args) {
        if (args.length < 1) {
            return;
        }
        int len = Integer.parseInt(args[0]);
        Random rand = new Random();
        int[] nums = new int[len];
        for (int i = 0; i < nums.length; i++) {
            nums[i] = rand.nextInt(300);
        }
        System.out.println(Arrays.toString(nums));
        sort(nums);
        System.out.println(Arrays.toString(nums));
    }

    public static void sort(int[] nums) {
        for (int end = nums.length - 1; end > 0; end--) {
            for (int p = (end - 1) / 2; p >= 0; p--) {
                int max = p;
                int left = p * 2 + 1;
                int right = p * 2 + 2;
                if (nums[left] > nums[max]) {
                    max = left;
                }
                if (right <= end && nums[right] > nums[max]) {
                    max = right;
                }
                if (max != p) {
                    swap(nums, max, p);
                }
            }
            swap(nums, 0, end);
        }
    }

    private static void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
