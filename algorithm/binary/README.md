# Binary

## [190. Reverse Bits](https://leetcode.com/problems/reverse-bits/description/)

```c++
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        n = ((n & 0xffff0000) >> 16) | ((n & 0x0000ffff) << 16);
        n = ((n & 0xff00ff00) >>  8) | ((n & 0x00ff00ff) <<  8);
        n = ((n & 0xf0f0f0f0) >>  4) | ((n & 0x0f0f0f0f) <<  4);
        n = ((n & 0xcccccccc) >>  2) | ((n & 0x33333333) <<  2);
        n = ((n & 0xaaaaaaaa) >>  1) | ((n & 0x55555555) <<  1);
        return n;
    }
};
```

Use the example to think
```
0000 0010 1001 0100 0001 1110 1001 1100

swap 16 bit
0001 1110 1001 1100 0000 0010 1001 0100

swap 8 bit
1001 1100 0001 1110 1001 0100 0000 0010

swap 4 bit
1100 1001 1110 0001 0100 1001 0010 0000

swap 2 bit
0011 0110 1011 0100 0001 0110 1000 0000

swap 1 bit
0011 1001 0111 1000 0010 1001 0100 0000
```

## [268. Missing Number](https://leetcode.com/problems/missing-number/description/)

Brute force
```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        // brute force
        sort(nums.begin(), nums.end());
        
        const int n = nums.size();
        
        for(int i = 0; i < n; i++) {
            if(nums[i] != i)
                return i;
        }

        return n;
    }
};
```

Bitwise
```c++
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int ans = 0;

        for(int i = 0; i <= nums.size(); i++)
            ans ^= i;

        for (int i = 0; i < nums.size(); i++)
            ans ^= nums[i];

        return ans;
    }
};
```

原理 `a ^ 1 ^ 2 ^ 3 = 1 ^ 2 ^ a ^ 3`

找到缺失的號碼

## 