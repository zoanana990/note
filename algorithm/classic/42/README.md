# 42. Trapping Rain Water

Brute Force:
```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size(), ans = 0;
        auto s_it = cbegin(height), e_it = cend(height);
        for(int i = 0; i < n; i++) {
            int l = *max_element(s_it, s_it + i + 1);
            int r = *max_element(s_it + i, e_it);
            ans += min(l, r) - height[i];
        }

        return ans;
    }
};
```

Result: Time Limit Exceeded

Improve that by dynamic programming
```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size(), ans = 0;
        vector<int> l(n), r(n);

        l[0] = height[0];
        r[n - 1] = height[n - 1];

        for(int i = 1; i < n; i++)
            l[i] = max(l[i - 1], height[i]);

        for(int i = n - 2; i >= 0; i--)
            r[i] = max(r[i + 1], height[i]);
        
        for(int i = 0; i < n; i++)
            ans += min(l[i], r[i]) - height[i];

        return ans;
    }
};
```

Furthermore, we can simplifiy that 
```
i = 0, l = 0, r = 3, ans = 0 + 0 - 0 = 0
i = 1, l = 1, r = 3, ans = 0 + 1 - 1 = 0
i = 2, l = 0, r = 3, ans = 0 + 1 - 0 = 1
...
```

On the above example, we do not need to use left and right simultaneously, and we only need to use the min one

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size(), ans = 0;
        int l = 0, r = n - 1, l_max = 0, r_max = 0;
        while(r > l) {
            l_max = max(l_max, height[l]);
            r_max = max(r_max, height[r]);

            if(l_max > r_max) {
                ans += r_max - height[r--];
            } else {
                ans += l_max - height[l++];
            }            
        }

        return ans;
    }
};
```

And the last solution is using the stack
```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size(), ans = 0;
        stack<int> wall;

        for(int i = 0; i < n; i++) {
            while(!wall.empty() && height[wall.top()] < height[i]) {
                int lowest = wall.top();
                wall.pop();

                if(wall.empty())
                    break;

                int h = min(height[i] - height[lowest], height[wall.top()] - height[lowest]);
                int width = i - wall.top() - 1;
                ans += h * width;
            }

            wall.push(i);
        }

        return ans;
    }
};
```