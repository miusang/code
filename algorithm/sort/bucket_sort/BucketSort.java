import java.util.Arrays;
import java.util.ArrayList;
import java.util.Random;

public class BucketSort {
    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("please int put num length.");
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
        int minVal = nums[0];
        for (int i = 0; i < nums.length; i++) {
            if (nums[i] > maxVal) {
                maxVal = nums[i];
            } else if (nums[i] < minVal) {
                minVal = nums[i];
            }
        }

        int bucketStep = nums.length;
        int bucketCount = (maxVal - minVal) / bucketStep + 1;
        ArrayList<ArrayList<Integer>>buckets = new ArrayList<>();
        for (int i = 0; i < bucketCount; i++) {
            buckets.add(new ArrayList<Integer>());
        }
        for (int i = 0; i < nums.length; i++) {
            int bucketIndex = (nums[i] - minVal) / bucketStep;
            buckets.get(bucketIndex).add(nums[i]);
        }
        for (int i = 0; i < buckets.size(); i++) {
            insertSort(buckets.get(i));
        }
        int k = 0;
        for (int i = 0; i < buckets.size(); i++) {
            for (int j = 0; j < buckets.get(i).size(); j++) {
                nums[k] = buckets.get(i).get(j);
                k++;
            }
        }
    }

    public static void insertSort(ArrayList<Integer> nums) {
        int j;
        for (int i = nums.size() - 1; i > 0; i--) {
            j = i;
            int tmp = nums.get(i - 1);
            while (j < nums.size() && nums.get(j) < tmp) {
                nums.set(j - 1, nums.get(j));
                j++;
            }
            nums.set(j - 1, tmp);
        }
    }
}
