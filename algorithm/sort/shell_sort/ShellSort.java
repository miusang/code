import java.util.Arrays;
import java.util.Random;

public class ShellSort {
    public static void main (String[] args) {
        int[] nums = new int[51];
        Random random = new Random();
        for (int i = 0; i < nums.length; i++) {
            nums[i] = random.nextInt(300);
        }
        System.out.println(Arrays.toString(nums));
        sort(nums);
        System.out.println(Arrays.toString(nums));
    }

    public static void sort(int[] nums) {
        int i,j;
        for (int gap = nums.length / 2; gap > 0; gap = gap / 2) {
            // if(gap == 1) return; just for check
            for (i = nums.length - gap; i >= gap ; i --) {
                j = i;
                int tmp = nums[i - gap];
                while (j < nums.length && nums[j] < tmp) {
                    nums[j - gap] = nums[j];
                    j += gap;
                }
                nums[j - gap] = tmp;
            }
        }
    }
}
