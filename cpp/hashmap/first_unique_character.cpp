#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> frequencies;

        for (char character : s) {
            ++frequencies[character];
        }

        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            if (frequencies[s[i]] == 1) {
                return i;
            }
        }

        return -1;
    }
};
