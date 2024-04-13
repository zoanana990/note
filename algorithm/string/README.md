# string

[125. Valid Palindrome](https://leetcode.com/problems/valid-palindrome/description/)
```c++
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while(right > left) {
            while(!isalnum(s[left])) {
                left++;
                if(left > s.size())
                    return true;
            }
                
            while(!isalnum(s[right])){
                right--;
                if(right < 0)
                    return true;
            }

            if(isupper(s[left]))
                s[left] = tolower(s[left]);
            if(isupper(s[right]))
                s[right] = tolower(s[right]);

            if(s[left] != s[right]) {
                return false;
            }
            left++, right--;    
        } 

        return true;
    }
};
```

Record the API in the string