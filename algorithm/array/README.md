# Array 的解題框架

陣列通常會遇到下面幾種出題方法：
1. 區間問題：這個需要配合動態規劃、貪婪演算法處理，比較棘手 (Medium to hard)
2. 雙指標問題：像是二元搜尋法、移動窗口和快慢指標等等
3. 前綴和(prefix sum): 這個等等也有框架說明

## Prefix Sum 技巧使用
參考: [prefix sum](https://blog.csdn.net/ch_609583349/article/details/106423315)

當題目中出現**子陣列的和、連續子陣列、除了自己以外的其他所有元素**等等的關鍵字可能就是用這個框架

例題一：[560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/description/)

brute force
```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        
        int count = 0, n = nums.size();

        for(int i = 0; i < n; i++) {
            int sum = 0;
            for(int j = i; j < n; j++) {
                sum += nums[j];
                if(sum == k) {
                    count++;
                }
            }
        }

        return count;
    }
};
```

We can use a vector to memorize the sum of the postfix,
Use **hashmap**