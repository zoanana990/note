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

## [207. Course Schedule](https://leetcode.com/problems/course-schedule/description/), **fail**

idea:
1. 先把每一堂課的擋修課有幾堂記錄下來
2. 先修沒有擋修的課，修完之後把那些需要這堂課的堂數 -1
3. 如果那些課現在也已經可以修了，就開始修那些課

怎麼修課呢？
使用 bfs 算法 + queue，queue 是用來看現在有哪些課要修的

當所有能修的課都修完之後檢查一下有沒有課沒有修到，有的話就是 false 擋修無限

Solution: topology sort
```c++
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        unordered_map<int, vector<int>> map;
        vector<int> indegree(numCourses, 0);
        queue<int> q;
        
        for(const auto& prerequisite : prerequisites) {
            map[prerequisite[1]].push_back(prerequisite[0]);
            indegree[prerequisite[0]]++;
        }
        
        for(int i = 0; i < numCourses; ++i) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }
        
        while(!q.empty()) {
            int curr = q.front();
            q.pop();
            numCourses--;
    
            for(int next : map[curr]) {
                if(--indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return numCourses == 0;
    }
};
```

dfs: make a graph first

```c++
class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // Build the directed graph
        vector<vector<int>> graph(numCourses);
        for (const auto& prerequisite : prerequisites) {
            graph[prerequisite[1]].push_back(prerequisite[0]);
        }
        
        vector<int> visited(numCourses, 0); // 0: not visited, 1: visiting, 2: visited
        
        // Apply DFS for each node
        for (int i = 0; i < numCourses; ++i) {
            if (!dfs(i, graph, visited)) {
                return false; // If there's a cycle, return false
            }
        }
        
        return true; // No cycle found, return true
    }
    
    // DFS function to check for cycle
    bool dfs(int course, vector<vector<int>>& graph, vector<int>& visited) {
        if (visited[course] == 1) return false; // If the current node is being visited, there's a cycle
        if (visited[course] == 2) return true;  // If the current node has been visited, no cycle
        
        visited[course] = 1; // Mark the current node as being visited
        
        // DFS on neighbors of the current node
        for (int neighbor : graph[course]) {
            if (!dfs(neighbor, graph, visited)) {
                return false;
            }
        }
        
        visited[course] = 2; // Mark the current node as visited
        
        return true;
    }
};
```