# Binary Search

In this document, I will demystify how binary search work, and the boundary condition there exist

**Binary search is very simple, but the bounadry condition, edge case is very tricky.**

## Template
```c++
int search(vector<int>& nums, int target) {
    int n = nums.size(), left = 0, right = n - 1;

    while(/* fucking boundary */) {
        /* avoid the overflow situation */
        int mid = left + (right - left) / 2;
        if(nums[mid] == target)
            /* Do something */
        else if(nums[mid] < target)
            /* update left */
        else if(nums[mid] > target)
            /* update right */
    }

    /* your return here */
}
```

There are several notes:
1. Do not use **`else`**, please use `else if` to clearly clearify your condition
2. Please use `int mid = left + (right - left) / 2;` instead of `int mid = (right + left) / 2;` avoid overflow condition.

## Basic one
[704. Binary Search](https://leetcode.com/problems/binary-search/description/), easy
```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n - 1;

        while(right >= left) {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return -1;
    }
};
```

1. Why the while loop condition is `=>` not `>`?
2. Why the left and right are `right = mid + 1` and `left = mid - 1` instead of `right = mid` or `left = mid`?
3. What is the disadvantage of this design?

There are several cases that we can show you
### Case 1, if we use `[left, right)` with `<=`?
```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n;

        while(right >= left) {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return -1;
    }
};
``` 

test case: `nums = {-1}`, `target = 2`, it would access nums[1] $\rightarrow$ failed

### Case 2, if we use `[left, right]` with `<`?
```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n - 1;

        while(right > left) {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return -1;
    }
};
```
It would miss an element to check
test case: `nums = {5}`, `target = 5`, it would miss `nums[0]` to check $\rightarrow$ failed

We can use a patch to let it to check the miss element, that is `nums[left]` at the end:
```diff
-        return -1;
+        return nums[left] == target ? left : -1;
```

### Case 3, if we use `left = mid` ?
```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n - 1;

        while(right >= left) {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid;
            else
                right = mid - 1;
        }

        return -1;
    }
};
```

It would be a infinite loop.
test case: `nums = {-1,0,3,5,9,12}`, `target = 2`, let's trace it

first iteration:
```txt
left = 0, nums[left] = -1
right = 5, nums[right] = 12
mid = 2, nums[mid] = 3
compare, right = mid - 1, right = 1
```

second iteration:
```txt
left = 0, nums[left] = -1
right = 1, nums[right] = 0
mid = 0, nums[mid] = -1
compare, left = mid ???
```

and infinite loop, time limit exceed $\rightarrow$ failed

### Case 4, if we have several duplicate element? find the first guy
```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n - 1;

        while(right >= left) {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target)
                return mid;
            else if(nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return -1;
    }
};
```
test case:
```
nums = [-1,2,2,2,2,12]
target = 2
```

The basic template cannot deal with this situation.
Example: [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/)

## A solution for lower bound and upper bound
[34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/)
```C++
enum {
    LOWER,
    UPPER
};
class Solution {
public:
    int search(vector<int>& nums, int target, int strategy) {
        int n = nums.size(), left = 0, right = n - 1;

        while(left <= right) {
            int mid = left + (right - left) / 2;

            if(nums[mid] == target) {
                if(strategy == LOWER) {
                    // update right
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else if(nums[mid] < target) {
                left = mid + 1;
            } else if(nums[mid] > target) {
                right = mid - 1;
            }
        }

        if(strategy == LOWER){
            if(left >= n || nums[left] != target)
                return -1;
        }else{
            if(right < 0 || nums[right] != target)
                return -1;
        }
        return strategy ? right : left;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = search(nums, target, LOWER);
        int right = search(nums, target, UPPER);

        return {left, right};
    }
};
```

First, we will use this case to tell you how to find the upper bound and lower bound

if the code is like this:
```c++
enum {
    LOWER,
    UPPER
};
class Solution {
public:
    int search(vector<int>& nums, int target, int strategy) {
        int n = nums.size(), left = 0, right = n - 1;

        while(left <= right) {
            int mid = left + (right - left) / 2;

            /* if the target is found, we need to update the boundary */
            if(nums[mid] == target) {
                if(strategy == LOWER) {
                    // update right
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else if(nums[mid] < target) {
                left = mid + 1;
            } else if(nums[mid] > target) {
                right = mid - 1;
            }
        }

        if(strategy == LOWER){
            if(left >= n || nums[left] != target)
                return -1;
        }
        /* Here is original boundary check */

        return strategy ? right : left;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = search(nums, target, LOWER);
        int right = search(nums, target, UPPER);

        return {left, right};
    }
};
```
you can see that, we check at lower bound but we do not do the boundary check at upper bound

Given a test case:
```txt
nums = [5,7,7,8,8,10]
target = 6
```
Let's trace the code:

#### Lower boundary (left side)
```txt
the parameter we use is 
int left = search(nums, target, LOWER);
in this case, int left = = search(nums, 6, LOWER);
```

Let's get into the function `search`
```
int n = 6, l = 0, r = 5;

> while(l <= r)
> mid = 2
> nums[mid] = 7
> nums[mid] > target
> right = mid - 1 = 1

>> left = 0, right = 1, mid = 0
>> nums[mid] = 5 < target = 6
>> left = mid + 1 = 1

>>> left = 1, right = 1, mid = 1
>>> nums[mid] = 7 > target = 6, right = mid - 1 = 0
>>> break the while loop
```
after the `while` loop
```
left = 1, nums[left] = 7
```
in `search`
```c++
        if(strategy == LOWER){
            if(left >= n || nums[left] != target)
                return -1;
        }
```
it will return `-1`

Thus, it there is no boundary check, it will return `1`, which is not expected

### Multi-thread version
```c++
enum {
    LOWER,
    UPPER
};
class Solution {
public:
    int search(vector<int>& nums, int target, int strategy) {
        int n = nums.size(), left = 0, right = n - 1;

        while(left <= right) {
            int mid = left + (right - left) / 2;

            if(nums[mid] == target) {
                if(strategy == LOWER) {
                    // update right
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else if(nums[mid] < target) {
                left = mid + 1;
            } else if(nums[mid] > target) {
                right = mid - 1;
            }
        }

        if(strategy == LOWER){
            if(left >= n || nums[left] != target)
                return -1;
        }else{
            if(right < 0 || nums[right] != target)
                return -1;
        }
        return strategy ? right : left;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 0) return {-1, -1};

        int num_threads = 2; // Number of threads
        vector<int> results(num_threads);
        vector<thread> threads;
        
        // int left = search(nums, target, LOWER);
        // int right = search(nums, target, UPPER);
        // Launch threads
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back([&, i]() {
                results[i] = search(nums, target, i);
            });
        }


        // Join threads
        for (auto& t : threads) {
            t.join();
        }

        // return {left, right};
        return {results[0], results[1]};
    }
};
```

### Optimization
```c++
class Solution {
public:
    void binary_search(vector<int> &nums, vector<int> &ans, int target, int low, int high) {
        if (high < low) return;
        int mid = low + (high - low) / 2;
        if (nums[mid] > target)
            binary_search(nums, ans, target, low, mid - 1);
        else if (nums[mid] < target)
            binary_search(nums, ans, target, mid + 1, high);
        else {
            int start = mid, end = mid;
            while (start >= 0 && nums[start] == target) start--;
            while (end < nums.size() && nums[end] == target) end++;
            ans.push_back(start + 1);
            ans.push_back(end - 1);
            return;
        }
    }

    vector<int> searchRange(vector<int> &nums, int target) {
        vector<int> ans;
        binary_search(nums, ans, target, 0, nums.size() - 1);
        if (ans.empty()) return {-1, -1};
        return ans;
    }
};
```

## Variation of binary search
### [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/submissions/1224637379/)

Brute force with binary search

We need to consider six section here
- nums[m] > nums[r] > target
- nums[m] > target > nums[r]
..., TODO

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n - 1;
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(nums[mid] == target) {
                return mid;
            } else if(nums[mid] > target) {
                if(target > nums[right]) {
                    right = mid - 1;
                } else if(nums[mid] <= nums[right]){
                    right = mid - 1;
                } else if(nums[mid] > nums[right]) {
                    left = mid + 1;
                }
            } else if(nums[mid] < target){
                if(nums[mid] >= nums[right]) {
                    left = mid + 1;
                } else if(target <= nums[right]){
                    left = mid + 1;
                } else if(target > nums[right]) {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};
```
### [981. Time Based Key-Value Store](https://leetcode.com/problems/time-based-key-value-store/description/)

Inlcuding data structure design.

```c++
class TimeMap {
private:
    unordered_map<string, vector<pair<int, string>>> map;
public:
    TimeMap() {}
    
    void set(string key, string value, int timestamp) {
        this->map[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        if(map.find(key) == map.end())
            return "";

        // binary search here, find the largest lower_bound
        int l = 0, r = map[key].size() - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(map[key][mid].first < timestamp) {
                l = mid + 1;
            } else if (map[key][mid].first > timestamp) {
                r = mid - 1;
            } else {
                return map[key][mid].second;
            }
        }

        return r >= 0 ? map[key][r].second : "";
    }
};

```

### [74. Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/description/)

Original:
```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // binary search for the first element and search the subarray
        int l = 0, r = matrix.size() - 1, idx;
        if(r > 0) {
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(matrix[mid][0] == target)
                    return true;
                else if(matrix[mid][0] < target)
                    l = mid + 1;
                else if(matrix[mid][0] > target)
                    r = mid - 1;
            }
        }
        if(r < 0)
            return false;
        cout << l << " " << r << endl;
        // find the 'r' index matrix
        idx = r;
        l = 0, r = matrix[idx].size() - 1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(matrix[idx][mid] == target)
                return true;
            else if(matrix[idx][mid] < target)
                l = mid + 1;
            else if(matrix[idx][mid] > target)
                r = mid - 1;
        }
        cout << "fuck" << endl;

        return false;
    }
};
```

How to merge them to one ?
```c++
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size(),
            row = 0, col = matrix[0].size() - 1;
			
        while (row < rows && col > -1) {
            int cur = matrix[row][col];
            if (cur == target) return true;
            else if (target > cur) row++;
            else if (target < cur) col--;
        }
        
        return false;
    }
};
```

### [153. Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/), **fail**
```c++
class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;

        while(l < r) {
            int m = l + (r - l) / 2;
            if(nums[m] > nums[r])
                l = m + 1;
            else
                r = m;
        }

        return nums[l];
    }
};
```

### Optimize, divide and conquer
```c++
class Solution {
public:
    int findMin(vector<int> &num) {
        return findMin(num, 0, num.size()-1);
    }
    
private:
    int findMin(const vector<int>& num, int l, int r)
    {
        // Only 1 or 2 elements
        if (l+1 >= r) return min(num[l], num[r]);
        
        // Sorted
        if (num[l] < num[r]) return num[l];
        
        int mid = l + (r-l)/2; 
        
        return min(findMin(num, l, mid-1), 
                   findMin(num, mid, r));
    }
};
```

## Application
### [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/description/)

