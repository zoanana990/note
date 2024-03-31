class Solution {
public:
    // Helper function for DFS
    void dfs(unordered_map <string, vector<string>> &graph, string &current, vector <string> &result) {
        while (!graph[current].empty()) {
            string next = graph[current].back();
            graph[current].pop_back();
            dfs(graph, next, result);
        }
        result.push_back(current);
    }

    vector <string> findItinerary(vector <vector<string>> &tickets) {
        unordered_map <string, vector<string>> graph;

        // Create the graph using tickets
        for (const auto &ticket: tickets) {
            graph[ticket[0]].push_back(ticket[1]);
            // Sort the destinations for lexical order
            sort(graph[ticket[0]].begin(), graph[ticket[0]].end(), greater<string>());
        }

        vector <string> result;
        string start = "JFK";
        dfs(graph, start, result);

        reverse(result.begin(), result.end()); // Reverse to get the correct order
        return result;
    }
};