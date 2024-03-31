class UnionFind {
public:
    UnionFind(int n) : parent(n + 1) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) {
            return false; // The edges x and y form a cycle
        }
        parent[rootX] = rootY;
        return true;
    }

private:
    std::vector<int> parent;
};

class Solution {
public:
    std::vector<int> findRedundantConnection(std::vector <std::vector<int>> &edges) {
        int n = edges.size();
        UnionFind uf(n);

        std::vector<int> result;

        for (const auto &edge: edges) {
            if (!uf.unite(edge[0], edge[1])) {
                // The edge forms a cycle, store it as a potential answer
                result = edge;
            }
        }

        return result;
    }
};