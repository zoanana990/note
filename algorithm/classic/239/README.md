# LeetCode 239. Sliding Window Maximum

Solution:
1. Sliding Window
2. Monotonic Stack
3. Priority Queue
4. Deque

### Sliding Window + deque
```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size(), l = 0;
        deque<int> window;
        vector<int> ans;

        for(int i = 0; i < n; i++) {
            while(!window.empty() && window.back() < nums[i])
                window.pop_back();
            window.push_back(nums[i]);

            if(i - k + 1 == l) {
                ans.push_back(window.front());
                if(nums[l] == window.front())
                    window.pop_front();
                l++;
            }

        }

        return ans;
    }
};
```

IDEA:
```txt
Array                              Monotonic Queue      Max
[1], 3, -1, -3, 5, 3, 6, 7         [1]                  -
[1, 3], -1, -3, 5, 3, 6, 7         [3] -> pop back because it is smaller than [3]
[1, 3, -1], -3, 5, 3, 6, 7         [3, -1]              [3] -> (l - r + 1 == k)
1, [3, -1, -3], 5, 3, 6, 7         [3, -1, -3]          [3] -> (l - r + 1 == k)
1, 3, [-1, -3, 5], 3, 6, 7         [-1, -3, 5]          [5]
...
```

Thus we need to shrink the window when the previous number is smaller than current.
And we need to push the front number in the window when the condition is fulled

### Sliding Window + priority queue
```c++
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        priority_queue<pair<int , int>> pq;
        vector<int>ans;
        int i = 0, j = 0;
        while(j < a.size()) {
            while(j - i < k)
                pq.push({a[j] , j++});

            while(!pq.empty() && j - pq.top().second > k)
                pq.pop();

            ans.push_back(pq.top().first);
            i++;
        }
        return ans;
    }
};
```