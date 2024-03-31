
class Solution {
public:
    vector<int> findRedundantConnection(vector <vector<int>> &edges) {
        int n = edges.size();
        vector<int> parent(n + 1, 0);

        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }

        vector<int> result;

        for (const auto &edge: edges) {
            int u = edge[0];
            int v = edge[1];

            int pu = find(parent, u);
            int pv = find(parent, v);

            if (pu == pv) {
                result = edge; // Save the redundant edge
            } else {
                parent[pv] = pu;
            }
        }

        return result;
    }

    int find(vector<int> &parent, int node) {
        while (parent[node] != node) {
            parent[node] = parent[parent[node]];
            node = parent[node];
        }
        return node;
    }

};