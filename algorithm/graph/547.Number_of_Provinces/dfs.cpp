class Solution {
public:
    int findCircleNum(std::vector <std::vector<int>> &isConnected) {
        int n = isConnected.size();
        int provinces = 0;
        std::vector<bool> visited(n, false);

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                dfs(isConnected, visited, i);
                ++provinces;
            }
        }

        return provinces;
    }

    void dfs(std::vector <std::vector<int>> &isConnected, std::vector<bool> &visited, int city) {
        visited[city] = true;

        for (int j = 0; j < isConnected.size(); ++j) {
            if (isConnected[city][j] == 1 && !visited[j]) {
                dfs(isConnected, visited, j);
            }
        }
    }
};