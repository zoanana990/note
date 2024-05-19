# Summary
# 演算法複習

## 二元搜尋 (Binary Search)
使用時機：
1. **遇到已經排序的陣列**
2. 面試官想要比 `O(n)` 還要小
3. 找到陣列的分割位置
4. 找到最大最小值使得某個條件被滿足

複雜度
- 時間複雜度 `O(log(n))`
- 空間複雜度 `O(1)`

### 標準模板
```c++
int search(vector<int>& nums, int target) {
    int n = nums.size(), left = 0, right = n - 1;

    while(left <= right) {
        /* avoid the overflow situation */
        int mid = left + (right - left) / 2;
        if(nums[mid] == target)
            /* Do something, Please double check the bounary */
        else if(nums[mid] < target)
            /* update left */
        else if(nums[mid] > target)
            /* update right */
    }

    /* Do something, Please double check the bounary */

    /* your return here */
}
```
有幾種變形：
1. 標準找值
   - [704. Binary Search](https://leetcode.com/problems/binary-search/description/)
2. 陣列的值有可能重複，請你找邊界點
   - [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/)

### 旋轉的排序陣列
```
1 2 3 4 5 6 7 8
```
旋轉過後
```
6 7 8 1 2 3 4 5
```
範例：


解法：分段討論，解法範例為 leetcode 81
```c++
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size(), l = 0, r = n - 1;

        while(l <= r) {
            int m = l + (r - l) / 2;
            if(nums[m] == target) {
                return true;
            } else if(nums[m] == nums[l] && nums[m] == nums[r]) {
                l++, r--;
            } else if(nums[m] < target) {
                if(nums[r] < nums[m]) {
                    l = m + 1;
                } else if(nums[r] >= target) {
                    l = m + 1;
                } else if(nums[r] >= nums[m] && nums[r] < target) {
                    r = m - 1;
                }
            } else if(nums[m] > target) {
                if(nums[r] < target) {
                    r = m - 1;
                } else if(nums[r] >= nums[m]) {
                    r = m - 1;
                } else if(nums[m] >= nums[r] && nums[r] >= target) {
                    l = m + 1;
                }
            }
        }

        return false;
    }
};
```

有幾種變形：
1. 標準找值
   - [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/description/), `medium`
2. 陣列的值有可能重複
   - [81. Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/), `medium`

### 應用題
這種比較麻煩，需要隨機應變：
- [875. Koko Eating Bananas](https://leetcode.com/problems/koko-eating-bananas/description/), `medium`
- [1011. Capacity To Ship Packages Within D Days](https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/description/), `medium`

複習：[Binary Search](../algorithm/binary_search/README.md)

## 雙指標 (Two Pointer)
使用時機：
1. 時間複雜度要求 `O(n)`
2. 要求原地操作，不可以使用額外的空間
3. 有子陣列 (subarray) 或是子字串 (substring) 的關鍵字
4. 有回文 (Palindrome) 的關鍵字

時間複雜度：`O(n)`

### 滑動窗口 (Sliding Window)


模板
```c++

```


### 相向指標

### 背離指標

## 前綴和 (Prefix Sum)


## 排序 (Sorting)
### 陣列排序 (Array Sort)
代表作：Quick Sort + Insertion Sort

範例：
- [912. Sort an Array](https://leetcode.com/problems/sort-an-array/description/)

從一開始的 quick sort 開始
```c++
#include <pthread.h>

class Solution {
public:
    void insertSort(vector<int> &nums, int start, int end) {
        for(int i = start; i <= end; i++) {
            int val = nums[i];
            int j = i;
            while(j > start && nums[j - 1] > val) {
                nums[j] = nums[j - 1];
                j -= 1;
            }
            nums[j] = val;
        }
    }
    int partition(vector<int> &nums, int start, int end) {
        int l = start - 1, r = start;

        for(;r < end; r++) {
            if(nums[r] < nums[end]) {
                l++;
                swap(nums[l], nums[r]);
            }
        }

        swap(nums[++l], nums[end]);
        return l;
    }
    void quickSort(vector<int>& nums, int start, int end) {
        if(start >= end)
            return;

        if(end - start < 22) {
            insertSort(nums, start, end);
            return;
        }

        int pivot = partition(nums, start, end);

        quickSort(nums, start, pivot - 1);
        quickSort(nums, pivot + 1, end);
    }
    
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
};
```
這是 quick sort 和 insertion sort 的結合
> time limit exceed

```c++
#include <pthread.h>

class Solution {
public:
void merge(vector<int>& nums, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = nums[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = nums[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            nums[k] = L[i];
            i++;
        } else {
            nums[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        nums[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        nums[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& nums, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);

        merge(nums, left, mid, right);
    }
}

vector<int> sortArray(vector<int>& nums) {
    mergeSort(nums, 0, nums.size() - 1);
    return nums;
}
};
```
Merge Sort

### 串列排序 (List Sort)
代表作：Merge Sort


## Binary Tree

## BFS

## DFS

## Dynamic Pogramming
三種題型

## Heap