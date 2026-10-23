#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> available;
        unordered_map<char, int> needed;

        for (char character : ransomNote) {
            ++needed[character];
        }

        for (char character : magazine) {
            ++available[character];
        }

        for (const auto& entry : needed) {
            auto count = available.find(entry.first);
            if (count == available.end() || count->second < entry.second) {
                return false;
            }
        }

        return true;
    }
};
