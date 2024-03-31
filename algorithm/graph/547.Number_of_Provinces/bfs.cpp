#include <vector>
#include <queue>

class Solution {
public:
    int findCircleNum(std::vector <std::vector<int>> &isConnected) {
        int n = isConnected.size();
        int provinces = 0;
        std::vector<bool> visited(n, false);

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                bfs(isConnected, visited, i);
                ++provinces;
            }
        }

        return provinces;
    }

    void bfs(std::vector <std::vector<int>> &isConnected, std::vector<bool> &visited, int startCity) {
        std::queue<int> q;
        q.push(startCity);
        visited[startCity] = true;

        while (!q.empty()) {
            int city = q.front();
            q.pop();

            for (int j = 0; j < isConnected.size(); ++j) {
                if (isConnected[city][j] == 1 && !visited[j]) {
                    q.push(j);
                    visited[j] = true;
                }
            }
        }
    }
};
