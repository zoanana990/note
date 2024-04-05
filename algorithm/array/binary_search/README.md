# Binary Search

In this document, I will demystify how binary search work, and the boundary condition there exist

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
test case: `nums = {-1,0,3,5,9,12}`, `target = 2`, it would miss `nums[0]` to check $\rightarrow$ failed


## Left Bound

## Right Bound