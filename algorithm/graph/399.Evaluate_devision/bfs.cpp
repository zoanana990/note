class Solution {
public:
    vector<double>
    calcEquation(vector <vector<string>> &equations, vector<double> &values, vector <vector<string>> &queries) {
        unordered_map <string, unordered_map<string, double>> graph;

        // Build the graph from equations and values
        for (int i = 0; i < equations.size(); ++i) {
            const string &A = equations[i][0];
            const string &B = equations[i][1];
            double value = values[i];

            graph[A][B] = value;
            graph[B][A] = 1.0 / value;
        }

        // Process queries using BFS
        vector<double> results;
        for (const auto &query: queries) {
            const string &start = query[0];
            const string &end = query[1];

            if (!graph.count(start) || !graph.count(end)) {
                // Either start or end variable is undefined
                results.push_back(-1.0);
            } else {
                double result = bfs(graph, start, end);
                results.push_back(result);
            }
        }

        return results;
    }

private:
    double bfs(unordered_map <string, unordered_map<string, double>> &graph, const string &start, const string &end) {
        queue <pair<string, double>> q;
        unordered_set <string> visited;

        q.push({start, 1.0});
        visited.insert(start);

        while (!q.empty()) {
            auto front = q.front();
            q.pop();
            const string &current = front.first;
            const double currentProduct = front.second;

            if (current == end) {
                return currentProduct;
            }

            for (const auto &neighbor: graph[current]) {
                const string &next = neighbor.first;
                const double edgeWeight = neighbor.second;

                if (visited.find(next) == visited.end()) {
                    q.push({next, currentProduct * edgeWeight});
                    visited.insert(next);
                }
            }
        }

        return -1.0;  // No path found
    }
};
