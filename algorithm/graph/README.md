# Graph

Method: DFS, BFS  with memorization and DP

## [542. 01 Matrix](https://leetcode.com/problems/01-matrix/description/)
1. BFS
```txt
0 0 0
0 1 0
1 1 1
```

first, initialized the matrix to 
```txt
0 0 0
0 M 0
M M M

all 0s are visited and in-queue
```

then the first iteration
```txt
0 0 0
0 1 0
1 M 1

all 0s and 1s are visited and in-queue
```

Implementation:
```c++
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        const int n = mat.size(), m = mat[0].size();
        queue<pair<int, int>> q;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int step = 0;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(mat[i][j] == 0) {
                    q.push({i, j});
                    visited[i][j] = true;
                } else {
                    mat[i][j] = INT_MAX;
                }
            }
        }

        while(!q.empty()) {
            int size = q.size();
            for(int i = 0; i < size; i++) {
                pair<int, int> position = q.front();
                q.pop();

                int x = position.first;
                int y = position.second;

                mat[x][y] = min(mat[x][y], step);

                for(int j = 0; j < 4; j++) {
                    int next_x = x + directions[j].first;
                    int next_y = y + directions[j].second;

                    if(next_x < 0 || next_y < 0 || next_x >= n || next_y >= m || visited[next_x][next_y])
                        continue;

                    q.push({next_x, next_y});
                    visited[next_x][next_y] = true;
                }
            }
            step++;
        }

        return mat;
    }
};
```
2. DFS
We can also use dfs to recurse it
```c++
class Solution {
public:
    void dfs(vector<vector<int>>& mat, vector<vector<int>>& result, int i, int j, int d) {
        if(i < 0 || j < 0 || i >= mat.size() || j >= mat[0].size() || d >= result[i][j])
            return;
        
        result[i][j] = d;

        dfs(mat, result, i + 1, j, d + 1);
        dfs(mat, result, i - 1, j, d + 1);
        dfs(mat, result, i, j + 1, d + 1);
        dfs(mat, result, i, j - 1, d + 1);
    }
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        const int n = mat.size(), m = mat[0].size();
        vector<vector<int>> result(n, vector<int>(m, INT_MAX));

        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(mat[i][j] == 0)
                    dfs(mat, result, i, j, 0);            

        return result;
    }
};
```

result: time limit exceeded

3. DP
Like leetcode 64, use minima path sum from top-left to bottom-right and also traverse the reverse direction and find the minima value!
```c++
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        const int n = mat.size(), m = mat[0].size();

        vector<vector<int>> dp(n, vector<int>(m, m+n));
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(mat[i][j] == 0)
                    dp[i][j] = 0;

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(i > 0)
                    dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                if(j > 0)
                    dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            }
        }

        for(int i = n - 1; i >= 0; i--) {
            for(int j = m - 1; j >= 0; j--) {
                if(i < n - 1)
                    dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
                if(j < m - 1)
                    dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
            }
        }
        
        return dp;
    }
};
```

## [133. Clone Graph](https://leetcode.com/problems/clone-graph/description/)
```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
    unordered_map<Node *, Node *> record;
public:
    Node* cloneGraph(Node* node) {
        if(node == nullptr)
            return node;
        else if(record.count(node))
            return record[node];

        Node *n_node = new Node(node->val, node->neighbors);
        record[node] = n_node;

        const int n = node->neighbors.size();
        for(int i = 0; i < n; i++) {
            Node *nn_node = cloneGraph(node->neighbors[i]);
            n_node->neighbors[i] = nn_node;
        }

        return n_node;
    }
};
```