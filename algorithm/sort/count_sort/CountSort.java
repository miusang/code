import java.util.Arrays;
import java.util.Random;

public class CountSort {
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
        int maxVal = nums[0];
        for(int num:nums) {
            maxVal = num > maxVal ? num : maxVal;
        }
        int[] tmps = new int[maxVal + 1];
        for (int i = 0; i < nums.length; i++) {
            tmps[nums[i]] += 1;
        }
        int index = 0;
        for (int i = 0; i < tmps.length; i++) {
            int j = 0;
            while (j < tmps[i]) {
                nums[index++] = i;
                j++;
            }
        }
    }
}
