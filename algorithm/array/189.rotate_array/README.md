# 189. Rotate Array

Idea:
[1, 2, 3, 4, 5, 6, 7]

reverse them first
[7, 6, 5, 4, 3, 2, 1]


and partial reverse, for instance, k = 2
[6, 7, 1, 2, 3, 4, 5]

and this is the solution

brute force:
```c++
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        vector<int> tmp{nums.begin(), nums.end()};

        for(int i = 0; i < k; i++) {
            nums[i] = tmp[i + n - k];
        }

        for(int i = 0; i < n - k; i++)
            nums[i + k] = tmp[i];
    }
};
```

> **we need to ask edge case, like, the edge case, `nums=[-1], k=2`**
> **and we can also ask k is greater or less than n**

```c++
class Solution {
public:
    void swap(int* a, int* b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;
    }
    void reverseArr(vector<int>& nums, int start, int end) {
        while(end > start) {
            swap(&nums[start++], &nums[end--]);
        }
    }
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if(n == 1)
            return;
        int t = k % n;
        reverseArr(nums, 0, n - 1);
        reverseArr(nums, 0, t - 1);
        reverseArr(nums, t, n - 1);
    }
};
```

Please use standard library:
```c++
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k = k % n;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin()+k, nums.end());
    }
};
```