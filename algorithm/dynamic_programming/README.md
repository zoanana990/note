# Dynamic Programming
The problem with dynamic programming generally revolves around finding the extremum, and its fundamental essence lies in enumeration.

Firstly, enumeration in dynamic programming is rather special, as such problems involve overlapping subproblems. If brute force enumeration is employed, the efficiency would be extremely low. Thus, utilizing memoization for optimized enumeration is necessary to avoid unnecessary computations.

Secondly, dynamic programming problems exhibit optimal substructure, enabling the extremum of subproblems to yield the extremum of the original problem.

Lastly, the challenges in dynamic programming stem from enumerating repetitive subproblems. Hence, it is crucial to establish the correct state transition equations to enumerate accurately.

The three aforementioned directions are:
1. Identifying overlapping subproblems
2. Identifying optimal substructure
3. Determining the state transition equations

Among these, finding the state transition equations is the most challenging. To correctly identify them, one must consider the following points:
1. What is the simplest scenario (base case)?
2. What are the possible states of the problem?
3. How does each state choice affect the outcome?
4. Define the DP array
5. How can repetitive subproblems be enumerated correctly?
6. Define the transfer function

## When dp?
1. When recursion alone O(2^n) won't work
2. Counting
3. Optimization

> Difference between DP and recursion with memorization

What if Dynamic Programming?
It is a programming method

Requirements:
1. Optimal Substructure
   - can be solved optimally by breaking it into subproblems and then recursively finding the optimal solutions to the subproblems
2. Overlapping subproblems
   - subproblems are overlapped such that we can compute only once and store the solution for future use
   - Reduce time complexity
   - If subproblems do not overlap -> divide and conquer (merge sort)
3. No-affect effect
   - The optimal solution of a subproblem will not change when it was used to solve a bigger problem optimally

Method
- Top-down: recursion with memorization
- Bottom-up: Dynamic Programming

Some problems:
- Fibonacci Sequence
- LCS
- Knapsack
- Floyd-Warshall
- Bellman-Ford

Patterns:
- leetcode 70 climbing stairs, `easy`
- Leetcode 62 Unique Paths, `medium`
- 

## [Leetcode 300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/description/)

### Dynamic Programming
Note: Dynamic programming is Mathematical Induction
> The first, the base case, proves the statement for $n = 0$ without assuming any knowledge of other cases.
> 
> The second case, the induction step, proves that if the statement holds for any given case $n = k$, then it must also hold for the next case $n = k + 1$

And the first, we need to define the `dp[i]` means. In this case, we define the `dp[i]` is the length of the longest increasing subarray ending in nums[i].

Here, we need to know, if we want to find a subarray is end with 3, we need to find a subarray which is end less than 3, and the length plus 1

that is
```txt
1 7 2 4 3
```

The length of subarray ends with 3, and the subarray is 
dp(3) = dp(2) + 1, where the dp(3) is the length of subarray end with 3

There is a complete example for this
```
nums = [1 7 2 4 3]
```
Start with nums[0] = 1
```
all dp[] elements are initialized to 1

i = 0, j = 0, dp[0] = 1

i = 1, j = 0, dp[1] = max(dp[1], dp[0] + 1) = 2;

i = 2, j = 0, dp[2] = max(dp[2], dp[0] + 1) = 2;
i = 2, j = 1, nums[1] > nums[2] -> skip

i = 3, j = 0, dp[3] = max(dp[3], dp[0] + 1) = 2;
i = 3, j = 1, nums[1] > nums[3] -> skip
i = 3, j = 2, dp[3] = max(dp[3], dp[2] + 1) = 3;
...
```

The procedure like that, so there are two conditon
1. the number is bigger than other array
2. find from the first elements

Source code:
```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> length_of_subarray(n, 1);
        int result = INT_MIN;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(nums[i] > nums[j]) {
                    length_of_subarray[i] = max(length_of_subarray[i], length_of_subarray[j] + 1);
                }
            }

            result = max(result, length_of_subarray[i]);
        }

        return result;
    }
};
```

> How to improve it ?

### Greedy and Binary Search
For two subsequence [1 2 8] and [3 4 5] which one is better?

[3 4 5] is better since the last element 5 is smaller than 8, which has more chance to expand, that is, [3 4 5 6] instead of [1 2 8 6]

dp[i] means the smllest ending number of subsequence that has length i + 1

for each number, we can use it to 
1. ectend the longest subsequence
2. replace a number to generte a better subsequence

```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp;
        int n = nums.size();

        dp.push_back(nums[0]);

        for(int i = 1; i < n; i++) {
            if(nums[i] > dp.back()) {
                dp.push_back(nums[i]);
            } else {
                int m = dp.size();
                if(nums[i] < dp[0])
                    dp[0] = nums[i];
                for(int j = m - 2; j >= 0; j--) {
                    if(nums[i] > dp[j]) {
                        dp[j + 1] = nums[i];
                        break;
                    }
                }
            }
        }

        return dp.size();
    }
};
```

Here, we can use STL functions, `lower_bound`
```c++
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp;
        int n = nums.size();

        for(auto d : nums) {
            auto i = lower_bound(dp.begin(), dp.end(), d);
            if(i == dp.end())
                dp.push_back(d);
            else
                *i = d;
        }

        return dp.size();
    }
};
```

## [Leetcode 322. Coin Change](https://leetcode.com/problems/coin-change/description/)

Brute Force (DFS)
```c++
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0)
            return 0;

        if(amount < coins[0])
            return -1;

        int result = INT_MAX, n = coins.size();

        for(int i = 0; i < n; i++) {
            int coin = coinChange(coins, amount - coins[i]);
            if(coin == -1)
                continue;
            result = min(result, coin + 1);
        }
        
        return result == INT_MAX ? -1 : result;
    }
};
```

> Result: Time limit exceed, Please write the memory to store the result

Recursive with memorization
```c++
class Solution {
public:
    int dp(vector<int>& coins, int amount, vector<int>& min_coins) {
        if(amount == 0)
            return 0;

        if(amount < 0)
            return -1;

        if(min_coins[amount] != INT_MAX)
            return min_coins[amount];

        int n = coins.size(), result = INT_MAX;

        for(int i = 0; i < n; i++) {
            int coin = dp(coins, amount - coins[i], min_coins);
            if(coin == -1)
                continue;
            result = min(result, coin + 1);
        }

        min_coins[amount] = result == INT_MAX ? -1 : result;

        return min_coins[amount];

    }
    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0)
            return 0;

        if(amount < 0)
            return -1;

        vector<int> cache(amount + 1, INT_MAX);

        return  dp(coins, amount, cache);
    }
};
```


TODO: Optimization

### [152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/description/)
Brute Force:
```c++
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = INT_MIN;
        int n = nums.size();
       
        // dp means, the result multiply from i to j
        vector<vector<int>> dp(n, vector<int>(n, INT_MIN));

        for(int i = 0; i < n; i++) {
            for(int j = i; j < n; j++) {
                if(i == j) {
                    dp[i][j] = nums[i];
                } else {
                    dp[i][j] = dp[i][j - 1] * nums[j];
                }
                ans = max(ans, dp[i][j]);
            }
        }

        return ans;
    }
};
```

Result: Time Limit Exceeded
Optimize, use a array with a pair, one is max and the other is min
```c++
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = nums[0];
        int n = nums.size();
       
        // dp means, the max or min result ends from nums[i]
        //           it may be stand from now or inherited from previous element
        // [0] standards max
        // [1] standards min
        vector<vector<int>> dp(n, vector<int>(2, 0));

        dp[0][0] = dp[0][1] = nums[0];

        for(int i = 1; i < n; i++) {
            // check the number is positive or negaative first
            vector<int> result = {nums[i] * dp[i - 1][1], nums[i] * dp[i - 1][0], nums[i]};
            sort(result.begin(), result.end());
            dp[i][0] = result[2];
            dp[i][1] = result[0];
            
            ans = max(ans, dp[i][0]);
        }

        return ans;
    }
};
```

Similar Qestion: [1567. Maximum Length of Subarray With Positive Product](https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/description/)
```c++
class Solution {
public:
    int getMaxLen(vector<int>& nums) {
        int n = nums.size();
        int ans = nums[0] > 0 ? 1 : 0;

        // [i][0] is length of positive number, [i][1] is length of negative number
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = nums[0] > 0 ? 1 : 0;
        dp[0][1] = nums[0] < 0 ? 1 : 0;

        for(int i = 1; i < n; i++) {
            if(nums[i] > 0) {
                dp[i][0] = dp[i - 1][0] + 1;
                dp[i][1] = (dp[i - 1][1] ? dp[i - 1][1] + 1 : 0);
            } else if(nums[i] < 0) {
                dp[i][1] = dp[i - 1][0] + 1;
                dp[i][0] = (dp[i - 1][1] ? dp[i - 1][1] + 1 : 0);
            } else {
                continue;
            }
            ans = max(ans, dp[i][0]);
        }

        return ans;
    }
};
```

We can improve it by space complexity
```c++
int getMaxLen(vector<int>& nums) {
    int maxLen = 0;
    int pCount = 0; // count of positive numbers
    int nCount = 0; // count of negative numbers
    for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] > 0) {
            pCount++;
            nCount = nCount ? nCount + 1 : 0;
        } else if (nums[i] < 0){ // nums[i] < 0
            int temp = pCount;
            pCount = nCount ? nCount + 1 : 0;
            nCount = temp + 1;
        } else {
            pCount = 0;
            nCount = 0;
            continue;
        }
        
        maxLen = max(maxLen, pCount);
    }

    return maxLen;
}
```

### [494. Target Sum](https://leetcode.com/problems/target-sum/description/)
```c++
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        const int n = nums.size();
        const int sum = accumulate(nums.begin(), nums.end(), 0);

        if(sum < target || target < -sum)
            return 0;

        vector<vector<int>> ways(n + 1, vector<int>(sum + sum + 1, 0));

        ways[0][sum] = 1;

        for(int i = 0; i < n; i++) {
            for(int j = nums[i]; j < 2 * sum + 1 - nums[i]; j++) {
                if(ways[i][j]) {
                    ways[i + 1][j + nums[i]] += ways[i][j];
                    ways[i + 1][j - nums[i]] += ways[i][j];
                }
            }
        }

        return ways[n][target + sum];
    }
};
```

### [416. Partition Equal Subset Sum](https://leetcode.com/problems/partition-equal-subset-sum/description/)

similar: 494, 416, 518

Solution: dp
```txt
dp[i][j]: whether we can sum to j using first i numbers
dp[i][j]: true if dp[i-1][j-num]
```

```c++
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        const int n = nums.size();
        const int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % 2)
            return false;

        vector<bool> dp(sum + 1, 0);
        for(int i = 0; i < n; i++) {
            vector<bool> tmp(dp.begin(), dp.end());
            for(int j = 1; j < sum + 1; j++)
                if(dp[j]) 
                    tmp[nums[i] + j] = true;
            swap(dp, tmp);
            dp[nums[i]] = true;
            if(dp[sum/2])
                break;
        }

        return dp[sum/2];
    }
};
```
