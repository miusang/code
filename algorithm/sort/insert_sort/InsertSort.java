import java.util.Arrays;
import java.util.Random;

public class InsertSort {
    public static void main(String[] args) {
        int[] nums = new int[50];
        Random random = new Random();
        for (int i = 0; i < nums.length; i++) {
            nums[i] = random.nextInt(300);
        }
        System.out.println(Arrays.toString(nums));
        sort(nums);
        System.out.println(Arrays.toString(nums));
    }

    public  static void sort(int[] nums) {
        int i,j;
        for (i = nums.length - 1; i > 0; i--) {
            int tmp = nums[i - 1];
            j = i;
            while (j < nums.length && nums[j] < tmp) {
                nums[j - 1] = nums[j];
                j++;
            }
            nums[j-1] = tmp;
        }
    }
}
