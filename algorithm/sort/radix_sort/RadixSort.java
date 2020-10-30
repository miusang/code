import java.util.Arrays;
import java.util.Random;

public class RadixSort {
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
        for (int num : nums) {
            maxVal = num > maxVal ? num : maxVal;
        }
        int bitCount = 1;
        while (maxVal / 10 > 0) {
            maxVal = maxVal / 10;
            bitCount++;
        }
        for (int i = 0; i < bitCount; i++) {
            int bit = 1;
            int j = 0;
            while (j < i) {
                bit = bit * 10;
                j++;
            }
            for (j = nums.length - 1; j >= 0; j--) {
                int tmp = nums[j];
                int k = j + 1;
                while (k < nums.length && (nums[k] / bit % 10) < 
                        (tmp / bit % 10)) {
                    nums[k - 1] = nums[k];
                    k++;
                }
                nums[k - 1] = tmp;
            }
        }
    }
}
