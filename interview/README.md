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

模板：參考 [sliding window 學習筆記](../algorithm/array/sliding_window/README.md)
```c++
void slidingWindow(string s, string t) {
    // we can use a hashtable, vector to be a window
    unordered_map<char, int> need, window;
    for(char c : t)
        need[c]++;

    int l = 0, r = 0, valid = 0, n = s.size();

    while(right < n) {
        char c = s[right];
        
        // expand right
        right++;

        // update the window

        while(/* condition for window need to shrink*/) {
            // remove the character in the window
            char d = s[left];

            //shrink the window
            left++;

            // update the window
        }
    }
}
```

範例：
從 [leetcode 3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/description/) 開始

題目規定最長的子字串沒有重複字元，想法：
1. 使用雜湊表紀錄每一個字元出現的數量，這邊可以替換成 `vector` 或是一般的陣列，只要可以記錄英文字母、數字和空白的儲存空間即可
2. 當字元沒有出現重複的情況時將區間擴大
3. 當字元出現重複向的時候將區間緊縮
4. 做完這一切之後更新區間的大小
```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // brute force
        int ans = 0;
        int n = s.size(), r = 0, l = 0;
        unordered_map<char, int> map;

        if(n <= 1)
            return n;

        while(r < n) {
            char c = s[r++];
            map[c]++;

            while(map[c] > 1) {
                char d = s[l++];
                map[d]--;
            }
            
            ans = max(ans, r - l);
        }

        return ans;
    }
};
```

範例二：[leetcode 76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/description/)
```c++
```

習題：
[leetcode 30. Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/)

這題並不是典型的滑動窗口的題目，但是精神是類似的，這題也告訴我們不能死背模板，必須搞清楚算法的精髓：

他不是典型的 `l`, `r` 指標，我們必須利用題目特性，也就是每一個字串的長度相同。因此想法很簡單，每一個字元都會把去走訪 word_len。例如：

```test case
s     = "barfoothefoobarman"
words = ["foo","bar"]
```

當然，一開始就要把 `words`  加入雜湊表：
```c++
unordered_map<string, int> dict;
for (const string& word : words) {
    dict[word]++;
}
```

我們需要先將 `foo` 和 `bar` 加到雜湊表中，從 0 開始走訪每一個單字，以這個測資為例：
0 3 6 9 12 15
1 4 7 ...
2 5 8 ...


```c++
vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> result;  // 用於存儲結果的向量
    if (words.empty() || s.empty()) return result;
    // 如果words或s是空的，直接返回空結果
    
    int word_len = words[0].length();
    // 獲取每個單詞的長度，假設所有單詞長度相同
    
    int num_words = words.size();
    int total_len = word_len * num_words;
    
    if (s.length() < total_len) return result;  
    // 如果s的長度小於總長度，不可能存在符合條件的子串，直接返回

    unordered_map<string, int> word_count;  
    // 記錄每個單詞出現次數的哈希表
    for (const auto& word : words) {
        word_count[word]++;  // 計數每個單詞在words中的出現次數
    }
    
    // 遍歷s的每個可能的起始位置，起始位置之間的間隔為word_len
    for (int i = 0; i < word_len; ++i) {
        unordered_map<string, int> current_count;  // 當前窗口內單詞的計數哈希表
        int start = i, count = 0;  // 初始化窗口的起始位置和單詞計數
        
        // 每次移動j的距離為word_len，因為我們要檢查固定長度的單詞
        for (int j = i; j <= s.length() - word_len; j += word_len) {
            string word = s.substr(j, word_len);  // 提取當前子串作為單詞
            if (word_count.find(word) != word_count.end()) {
                current_count[word]++;  // 如果單詞在word_count中，增加當前計數
                count++;
                
                // 如果當前單詞的計數超過了在words中的計數，需要縮小窗口
                while (current_count[word] > word_count[word]) {
                    string left_word = s.substr(start, word_len);  // 獲取窗口最左邊的單詞
                    current_count[left_word]--;  // 減少最左邊單詞的計數
                    count--;  // 單詞計數減少
                    start += word_len;  // 窗口起始位置右移
                }
                
                // 如果當前窗口內的單詞數等於words中的單詞數，則找到了一個符合條件的起始位置
                if (count == num_words) {
                    result.push_back(start);
                }
            } else {
                // 如果單詞不在word_count中，重置當前計數並移動起始位置
                current_count.clear();
                count = 0;
                start = j + word_len;
            }
        }
    }
    
    return result;  // 返回結果
}
```

### 相向指標

### 背離指標

## 前綴和 (Prefix Sum)
[leetcode 523. Continuous Subarray Sum](https://leetcode.com/problems/continuous-subarray-sum/description/)
```c++
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        if(n < 2)
            return false;

        unordered_map<int, int> prefix_sum;
        int sum = 0;
        prefix_sum[0] = -1;

        for(int i = 0; i < n; i++) {
            sum += nums[i];
            sum %= k;

            if(sum == 0 && i)
                return true;
            
            if(prefix_sum.count(sum)) {
                if(i - prefix_sum[sum] > 1)
                    return true;
            } else 
                prefix_sum[sum] = i;
        }

        return false;
    }
};
```

[Leetcode 848. Shifting Letters](https://leetcode.com/problems/shifting-letters/description/)
```c++
class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
        int n = shifts.size();
        vector<int> sum(n, 0);
        string ans;

        sum[n - 1] = shifts[n - 1] % 26;
        for(int i = n - 2; i >= 0; i--) {
            int prefix = sum[i + 1] + shifts[i] % 26;
            sum[i] = prefix % 26;
        }

        for(int i = 0; i < n; i++) {
            int shift = sum[i];
            int t = s[i] + shift;
            if(t > 'z')
                t = t - 'z' + 'a' - 1;
            ans += (char)t;
        }

        return ans;
    }
};
```

接下來進行空間複雜度和時間複雜度的優化
```c++
class Solution {
public:
    string shiftingLetters(string s, vector<int>& shifts) {
        int n = shifts.size();
        int sum = 0;

        for(int i = n - 1; i >= 0; i--) {
            sum += shifts[i] % 26;
            sum %= 26;

            int shift = sum;
            int t = s[i] + shift;
            if(t > 'z')
                t = t - 'z' + 'a' - 1;
            s[i] = t;
        }

        return s;
    }
};
```

[Leetcode 930.Binary Subarrays with Sum](https://leetcode.com/problems/binary-subarrays-with-sum/description/)
```c++
class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int, int> sum;
        int acc = 0, ans = 0;
        sum[0]++;
        for(auto n : nums) {
            acc += nums[i];

            if(sum.count(acc - goal))
                ans += sum[acc - goal];

            sum[acc]++;
        }

        return ans;
    }
};
```

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
題型:
1. 石頭問題 (遊戲問題)
2. 戳氣球問題
3. 子陣列問題
4. 回文問題 (Palindrome)

### 戳氣球問題
範例：
- [139. Word Break](https://leetcode.com/problems/word-break/description/), `medium`
- [813. Largest Sum of Averages](https://leetcode.com/problems/largest-sum-of-averages/description/), `medium`
- [312. Burst Balloons](https://leetcode.com/problems/burst-balloons/description/), `hard`


先從 [813. Largest Sum of Averages](https://leetcode.com/problems/largest-sum-of-averages/description/) 這題開始
```c++

```

## Heap