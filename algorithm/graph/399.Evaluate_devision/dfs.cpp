#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
public:
    vector<double>
    calcEquation(vector <vector<string>> &equations, vector<double> &values, vector <vector<string>> &queries) {
        // Build the graph
        unordered_map <string, unordered_map<string, double>> graph;
        for (int i = 0; i < equations.size(); ++i) {
            const string &a = equations[i][0];
            const string &b = equations[i][1];
            double value = values[i];
            graph[a][b] = value;
            graph[b][a] = 1.0 / value;
        }

        // Process queries
        vector<double> results;
        for (const auto &query: queries) {
            const string &start = query[0];
            const string &end = query[1];
            unordered_set <string> visited;
            double result = dfs(graph, start, end, visited);
            results.push_back(result);
        }

        return results;
    }

private:
    double
    dfs(unordered_map <string, unordered_map<string, double>> &graph, const string &current, const string &target,
        unordered_set <string> &visited) {
        if (graph.find(current) == graph.end() || graph.find(target) == graph.end()) {
            // Either current or target variable is undefined
            return -1.0;
        }

        if (current == target) {
            // Reached the target variable
            return 1.0;
        }

        visited.insert(current);

        for (const auto &neighbor: graph[current]) {
            const string &next = neighbor.first;
            if (visited.find(next) == visited.end()) {
                double result = dfs(graph, next, target, visited);
                if (result != -1.0) {
                    // Multiply the result by the edge weight to get the final answer
                    return result * graph[current][next];
                }
            }
        }

        return -1.0;
    }
};

int main() {
    Solution solution;

    vector <vector<string>> equations1 = {{"a", "b"},
                                          {"b", "c"}};
    vector<double> values1 = {2.0, 3.0};
    vector <vector<string>> queries1 = {{"a", "c"},
                                        {"b", "a"},
                                        {"a", "e"},
                                        {"a", "a"},
                                        {"x", "x"}};
    vector<double> output1 = solution.calcEquation(equations1, values1, queries1);
    for (double result: output1) {
        cout << result << " ";
    }
    cout << endl;  // Output: 6.00000 0.50000 -1.00000 1.00000 -1.00000

    return 0;
}
