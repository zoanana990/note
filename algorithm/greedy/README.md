# Greedy Algorithm

[Traditional Chinese Version](./tw_readme.md)

Greedy Algorithm is a short-sighted algorithm that only considers the current optimal solution. 
To use this algorithm, you need to meet a certain characteristic: each step is a local optimal solution and finally the overall optimal solution is reached.
Here are a few examples of this greedy nature.

> Note: Greedy algorithm has no template!!!
> You can simulate it manually during the interview

## [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/submissions/1161302468/)
```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = height.size() - 1, ans = -1;

        while(right > left) {
            int area = min(height[left], height[right]) * (right - left);
            ans = max(ans, area);
            if(height[right] > height[left])
                left++;
            else
                right--;
        }

        return ans;
    }
};
```

## jump game
### [jump game i](https://leetcode.com/problems/jump-game/description/)
> hint: we can use dynamic programming first

IDEA: we can use a vector to record the step we have
```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1);
        dp[0] = nums[0];
        for(int i = 1; i < n; i++)
            if(dp[i - 1] > 0)
                dp[i] = max(dp[i - 1] - 1, nums[i]);

        return dp.back() > -1 ? true : false;
    }
};
```

here, we can see that, if we still have the step, we will return true

in another idea, we can calculate the index we can move, like this
but we need to set a lower boundary, that is the farest index need to greater than current index
(it is moving, if it is freeze at some index, that is fail)

```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int max_index = 0;
        for(int i = 0; i < n - 1; i++) {
            max_index = max(max_index, i + nums[i]);
            if(max_index <= i)
                return false;
        }
        return true;
    }
};
```
Note: when we arrive index n, that is success, and at that time, we do not need the step anymore

> This point need to check with interviwer.

### [jump game ii](https://leetcode.com/problems/jump-game-ii/submissions/562754279/)
Similarly, we start from dynamic programming
```c++
class Solution {
public:
    int jump(vector<int>& nums) {
        // this is the size of nums
        int n = nums.size();

        // this is the vector to record the step the element need to jump to
        vector<int> dp(n, n);
        return dp_(nums, dp, 0);
    }

    int dp_(const vector<int>& nums, vector<int>& dp, int p) {
        int n = nums.size();

        // terminate condition, it is no need to traverse
        if(p >= n - 1)
            return 0;

        if(dp[p] != n) return dp[p];
        for(int i = 1; i <= nums[p]; i++) {
            int s = dp_(nums, dp, p+i);
            dp[p] = min(dp[p], s + 1);
        }

        return dp[p];
    }
};
```

and also, we can refine it, we can use greedy algorithm, the idea is we do not need to calculate
every possible, we only need to calculate the best one.
```c++
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int end = 0;
        int farest = 0;
        int jumps = 0;

        for(int i = 0; i < n - 1; i++) {
            farest = max(nums[i] + i, farest);
            if(end == i) {
                jumps++;
                end = farest;
            }
        }

        return jumps;
    }
};
```

## Interval problems
### [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/description/)
```c++
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        sort(intervals.begin(), intervals.end());

        // we only need to check the first one,
        // if the first one is less than the last one[1] need to go next
        // if not then merge
        vector<vector<int>> ans;
        for(int i = 1; i < n; i++) {
            if(intervals[i][0] <= intervals[i - 1][1]){
                // merge
                intervals[i][0] = min(intervals[i-1][0], intervals[i][0]);
                intervals[i][1] = max(intervals[i-1][1], intervals[i][1]);
            }
            else{
                ans.push_back(intervals[i-1]);
            }
        }
        ans.push_back(intervals[n-1]);

        return ans;
    }
};
```

### interval scheduling
There is a classic greedy algorithm problem, please calculate how many independent intervals this array has
```c++
int interval_schedule(vector<vector<int>>& intervals) {
    int n = intervals.size();
    if (n == 0)
        return 0;

    sort(intervals.begin(), intervals.end(), compare);

    int count = 1;
    int end = intervals[0][1];

    for(auto i:intervals) {
        int start = i[0];
        if(start >= end) {
            count++;
            end = i[1];
        }
    }

    return count;
}
```
Application: [435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/description/)

Here is another solution for Leetcode 435