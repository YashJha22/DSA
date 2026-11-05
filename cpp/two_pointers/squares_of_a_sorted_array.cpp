#include <cstdlib>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;
        int write = right;
        vector<int> result(nums.size());

        while (left <= right) {
            if (abs(nums[left]) > abs(nums[right])) {
                result[write] = nums[left] * nums[left];
                ++left;
            } else {
                result[write] = nums[right] * nums[right];
                --right;
            }
            --write;
        }

        return result;
    }
};
