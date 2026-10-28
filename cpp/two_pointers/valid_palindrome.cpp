#include <cctype>
#include <string>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.length() - 1;

        while (left < right) {
            // 1. Skip junk characters on the left
            while (left < right && !isalnum(s[left])) {
                left++;
            }

            // 2. Skip junk characters on the right
            while (left < right && !isalnum(s[right])) {
                right--;
            }

            // 3. Compare the letters (converted to lowercase)
            if (tolower(s[left]) != tolower(s[right])) {
                return false; // Mismatch found, not a palindrome!
            }

            // 4. They match! Move both fingers inward
            left++;
            right--;
        }

        return true; // Fingers met in the middle, it's a palindrome!
    }
};
