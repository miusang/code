import java.util.Arrays;
import java.util.Random;

public class SelectSort {
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
        sort(nums);
        System.out.println(Arrays.toString(nums));
    }

    public static void sort(int[] nums) {
        for (int i = 0; i < nums.length; i++) {
            int min_val = nums[i];
            int min_index = i;
            for (int j = i; j < nums.length; j++) {
                if (nums[j] < min_val) {
                    min_val = nums[j];
                    min_index = j;
                }
            }
            if (min_index != i) {
                swap(nums, min_index, i);
            }
        }
    }

    private static void swap(int[] nums, int i, int j) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    }
}
