#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> indices;

        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            int complement = target - nums[i];
            auto match = indices.find(complement);
            if (match != indices.end()) {
                return {match->second, i};
            }

            indices[nums[i]] = i;
        }

        return {};
    }
};
