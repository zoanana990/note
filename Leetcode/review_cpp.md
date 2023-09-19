# Review C++ STL
這篇文章是用來複習 `C++ STL` 的語法。

相關文件的用法可以參考

## 動態陣列 `vector`

### 初始化方法
```cpp

int n = 7, m = 8;

// 初始化一個 int 類型的空陣列
vector<int> nums;

// 初始化一個大小為 n，陣列的值預設都為 0
vector<int> nums(n);

// 初始化一個元素為 1, 3, 5 的陣列 nums
vector<int> nums(1, 3, 5);

// Initialize an array of size n and value 2
vector<int> nums(n, 2);

// Initialize a two dimension array
vector<vector<int>> dp

// Initialize a m*n array the value are true
vector<vector<bool>> dp(m, vector<bool>(n, true));
```

## 字串 `string`

## 雜湊表 `unordered_map`

## 雜湊集合 `unordered_set`

## 佇列 `queue`

## 堆疊 `stack`