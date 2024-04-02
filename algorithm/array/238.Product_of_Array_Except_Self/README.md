# 238. Product of Array Except Self

Limitation in this subjects:
> You must write an algorithm that runs in O(n) time and without using the division operation.

Thus, I have no idea. And the solution is, using three vector to record it.

idea:
vector<int> left, is used for all the left product for the index i
vector<int> right, is used for all the right product for the index i
and the answer is left * right

source code:
```c++
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> left(n, 1), right(n, 1), ans(n);

        for(int i = 1; i < n; i++)
            left[i] = left[i - 1] * nums[i - 1];
        
        for(int i = n - 2; i >= 0; i--)
            right[i] = right[i + 1] * nums[i + 1];
        
        for(int i = 0; i < n; i++)
            ans[i] = left[i] * right[i];
        
        return ans;
    }
};
```
