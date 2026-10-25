#include <cstddef>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> removeDuplicates(vector<int>& arr) {
        if (arr.empty()) {
            return arr;
        }

        std::size_t low = 0;
        for (std::size_t high = 1; high < arr.size(); ++high) {
            if (arr[high] != arr[low]) {
                arr[++low] = arr[high];
            }
        }

        arr.resize(low + 1);
        return arr;
    }
};
