# Sliding Window

> Sliding window has a fixed template to use, so please grasp this topic and practice.

## Concept
```c++
int left = 0, right = 0, n = nums.size();

while(right < n) {
    windos.add(nums[right]);
    while(/* window need to shrink*/) {
        window.remove(nums[left]);
        left++;
    }
}
```

### Template
```c++
void slidingWindow(string s, string t) {
    // we can use a hashtable, vector to be a window
    unordered_map<char, int> need, window;
    for(char c : t)
        need[c]++;

    int l = 0, r = 0, valid = 0, n = s.size();

    while(right < n) {
        char c = s[right];
        
        // expand right
        right++;

        // update the window

        while(/* condition for window need to shrink*/) {
            // remove the character in the window
            char d = s[left];

            //shrink the window
            left++;

            // update the window
        }
    }
}
```

Concepts in sliding window:
1. Initialize the left and right pointers to zero, and consider intervals as "left-closed and right-open".
2. Expand the right window until the string meets the specified requirement.
3. Shrink the left window until the string no longer meets the requirement.
4. Repeat steps 2 and 3 until the right pointer reaches the boundary.

When using the template, consider the following conditions:
1. When expanding the right window, update necessary data.
2. Decide when to shrink the window from the left side.
3. When shrinking the window, identify data to delete.
4. Determine whether to update the answer during expansion or shrinking.

An example, [leetcode 76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/description/)

Description:
> Given two strings `s` and `t` of lengths `m` and `n` respectively, return the minimum window substring of `s` such that every character in `t` (including duplicates) is included in the window. If there is no such substring, return the empty string `""`.
> 
> The testcases will be generated such that the answer is unique.

Constraints:
> 1. `m == s.length`
> 2. `n == t.length`
> 3. `1 <= m, n <= 105`
> 4. `s` and `t` consist of uppercase and lowercase English letters.

```c++
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<int, int> need, window;
        int n = s.size(), m = t.size(), len = INT_MAX;
        int left = 0, right = 0, valid = 0, start = 0;

        for(auto c: t)
            need[c]++;

        while(right <= n) {
            char c = s[right++];
            if(need.count(c)) {
                window[c]++;
                if(window[c] == need[c])
                    valid++;
            }

            while(valid == need.size()) {
                if(right - left < len) {
                    start = left;
                    len = right - left;
                }

                char d = s[left++];

                if(window.count(d)) {
                    if(window[d] == need[d])
                        valid--;
                    window[d]--;
                }
            }
        }

        return len == INT_MAX ? "" : s.substr(start, len);
    }
};
```

The first practice, [567. Permutation in String](https://leetcode.com/problems/permutation-in-string/description/)

And the first method is brute force, because we need to every algorithm is derived by brute force
```c++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.size(), m = s2.size(), times = m - n;
        unordered_map<char, int> map;

        for(auto s : s1)
            map[s]++;

        for(int i = 0; i <= times; i++) {
            unordered_map<char, int> check(map);
            int valid = 0;
            for(int j = i; j < i + n; j++) {
                check[s2[j]]--;
                if(check[s2[j]] == 0)
                    valid++;
            }

            if(valid == map.size())
                return true;
        }
            
        return false;
    }
};
```
Time complexity is $O(\frac{n^2}{2})$

And in this code, we can see that, the sliding window method
```c++
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n = s1.size(), m = s2.size();
        int valid = 0, l = 0, r = 0;
        unordered_map<char, int> map, window;

        for(auto s : s1)
            map[s]++;

        // we need to check the window boundary
        while(r < m) {
            char c = s2[r++];
            if(map.count(c)) {
                window[c]++;
                if(window[c] == map[c])
                    valid++;
            }

            // shrink the window
            while((r - l) >= n) {
                // update the ans
                if(valid == map.size()) {
                    return true;
                }

                char d = s2[l++];
                if(map.count(d)) {
                    if(window[d] == map[d])
                        valid--;
                    window[d]--;
                }
            }
        }
            
        return false;
    }
};
```

Time complexity is $O({2n})$

The second practice [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/description/)
```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // brute force
        int ans = 0;
        int n = s.size();

        if(n <= 1)
            return n;

        for(int i = 0; i < n; i++) {
            unordered_map<char, int> map;
            for(int j = i; j < n; j++) {
                map[s[j]]++;
                if(map[s[j]] > 1) {
                    break;
                }
            }

            ans = ans > map.size() ? ans : map.size();
        }

        return ans;
    }
};
```

Optimized:
```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // brute force
        int ans = 0;
        int n = s.size(), r = 0, l = 0;
        unordered_map<char, int> map;

        if(n <= 1)
            return n;

        while(r < n) {
            char c = s[r++];
            map[c]++;

            while(map[c] > 1) {
                char d = s[l++];
                map[d]--;
            }
            
            // update answer
            ans = max(ans, r - l);
        }

        return ans;
    }
};
```

## Difficult subject
[Leetcode 30. Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/)