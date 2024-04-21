# 518

Brute force with dfs
```c++
class Solution {
public:
    void dfs(int amount, vector<int>& coins, int& ways, int start) {
        if(amount == 0) {
            ways++;
            return;
        } else if (amount < 0)
            return;
        const int n = coins.size();
        for(int i = start; i < n; i++) {
            dfs(amount - coins[i], coins, ways, i);
        }
    }
    int change(int amount, vector<int>& coins) {
        int ways = 0;
        dfs(amount, coins, ways, 0);
        return ways;
    }
};
```

Improve it with memorization

Actually, it is `hard` level

IDEA:
1. Check status and choice
   - Status: the amount remain, and the coins you choose
   - Choice: Use this coin or not
2. Check the definition of dp array
   - `dp[i][j]`: when we use `coins[0 ~ i]` there are `dp[i][j]` methods
   - There is a base case: `dp[0][...] = 0, dp[...][0] = 1`
3. Define the transfer function
   - if we do not use `coins[i]`, the result is equal to previous, that is, `dp[i-1][j]`
   - if we use `coins[i]`, the result is equal to `dp[i][j-coins[i-1]]` (i starts from 1)
4. Check the boundary condition

```c++
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        const int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));

        for(int i = 0; i <= n; i++)
            dp[i][0] = 1;
        for(int j = 0; j <= amount; j++)
            dp[0][j] = 0;

        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= amount; j++) {
                if(j - coins[i - 1] >= 0)
                    dp[i][j] = dp[i][j - coins[i - 1]] + dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }

        return dp[n][amount];
    }
};
```

We can reduce the dimension:
```c++
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        const int n = coins.size();
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for(int i = 0; i < n; i++)
            for(int j = 0; j <= amount; j++)
                if(j - coins[i] >= 0)
                    dp[j] = dp[j] + dp[j - coins[i]];
        
        return dp[amount];
    }
};
```