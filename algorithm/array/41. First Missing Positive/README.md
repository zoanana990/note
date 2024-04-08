# 41. First Missing Positive

無限交換術

```c++
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        nums.push_back(0);

        // 將所有元素按照 0 ~ n 排好
        for (int i = 0 ; i < n; ++i)
            while(nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i]])
                swap(nums[i], nums[nums[i]]);

        // 檢查哪個元素不存在
        for (int i = 1; i <= n; ++i)
            if (nums[i] != i)
                return i;
        return n + 1;
    }
};
```

舉一個例子：
```txt
[3, 1, 4, -1]
一開始後面補 0，[3, 1, 4, -1, 0]
i = 0, [3, 1, 4, -1, 0], nums[i] = nums[0] != nums[nums[i]] = nums[3] = -1，交換
i = 1, [-1, 1, 4, 3, 0], nums[i] = nums[1] == nums[nums[i]] = nums[1]
i = 2, [-1, 1, 4, 3, 0], nums[i] = nums[2] != nums[nums[i]] = nums[4] = 0, 交換
i = 3, [-1, 1, 0, 3, 4]
i = 4, [-1, 1, 0, 3, 4]
```

下次走訪的時候從 i = 1 開始
```txt
1, 0 != 2
return 2
```