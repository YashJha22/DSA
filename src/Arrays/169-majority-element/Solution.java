import java.util.HashMap;

class Solution {
    public int majorityElement(int[] nums) {
        HashMap<Integer, Integer> freq = new HashMap<>();
        int res = 0;
        int majority = 0;

        for (int n : nums) {
            freq.put(n, 1 + freq.getOrDefault(n, 0));

            if (freq.get(n) > majority) {
                res = n;
                majority = freq.get(n);
            }
        }
        return res;
    }
}
